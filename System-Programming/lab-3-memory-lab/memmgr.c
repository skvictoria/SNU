//--------------------------------------------------------------------------------------------------
// System Programming                       Memory Lab                                   Fall 2020
//
/// @file
/// @brief dynamic memory manager
/// @author <yourname>
/// @studid <studentid>
//--------------------------------------------------------------------------------------------------


// Dynamic memory manager
// ======================
// This module implements a custom dynamic memory manager.
//
// Heap organization:
// ------------------
// The data segment for the heap is provided by the dataseg module. A 'word' in the heap is
// eight bytes.
//
// Implicit free list:
// -------------------
// - minimal block size: 32 bytes (header +footer + 2 data words)
// - h,f: header/footer of free block
// - H,F: header/footer of allocated block
//
// - state after initialization
//
//         initial sentinel half-block                  end sentinel half-block
//                   |                                             |
//   ds_heap_start   |   heap_start                         heap_end       ds_heap_brk
//               |   |   |                                         |       |
//               v   v   v                                         v       v
//               +---+---+-----------------------------------------+---+---+
//               |???| F | h :                                 : f | H |???|
//               +---+---+-----------------------------------------+---+---+
//                       ^                                         ^
//                       |                                         |
//               32-byte aligned                           32-byte aligned
//
// - allocation policies: first, next, best fit
// - block splitting: always at 32-byte boundaries
// - immediate coalescing upon free
//


#include <assert.h>
#include <error.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "dataseg.h"
#include "memmgr.h"

void mm_check(void);


static void *ds_heap_start = NULL;                     ///< physical start of data segment
static void *ds_heap_brk   = NULL;                     ///< physical end of data segment
static void *heap_start    = NULL;                     ///< logical start of heap
static void *heap_end      = NULL;                     ///< logical end of heap
static int  PAGESIZE       = 0;                        ///< memory system page size
static int  mm_initialized = 0;                        ///< initialized flag (yes: 1, otherwise 0)
static int  mm_loglevel    = 0;                        ///< log level (0: off; 1: info; 2: verbose)

static void *next_block    = NULL;

static void *(*get_block)(size_t) = NULL; // function pointer
                     // it can point to any function that returns void*, takes one size_t argument

#define MAX(a, b)          ((a) > (b) ? (a) : (b))     ///< MAX function

#define TYPE               unsigned long               ///< word type of heap
#define TYPE_SIZE          sizeof(TYPE)                ///< size of word type

#define ALLOC              1                           ///< block allocated flag
#define FREE               0                           ///< block free flag
#define STATUS_MASK        ((TYPE)(0x7))               ///< mask to retrieve flagsfrom header/footer
#define SIZE_MASK          (~STATUS_MASK)              ///< mask to retrieve size from header/footer

#define CHUNKSIZE          (1*(1 << 12))               ///< size by which heap is extended

#define BS                 32                          ///< minimal block size. Must be a power of 2
#define BS_MASK            (~(BS-1))                   ///< alignment mask

#define ROUND_UP(w)        (((w)+BS-1)/BS*BS)           ///< round up to next multiple of block size
#define ROUND_DOWN(w)      ((w)/BS*BS) 

#define WORD(p)            ((TYPE)(p))                 ///< convert pointer to TYPE
#define PTR(w)             ((void*)(w))                ///< convert TYPE to void*

#define PREV_PTR(p)        ((p)-TYPE_SIZE)             ///< get pointer to word preceeding p

#define PACK(size,status)  ((size) | (status))         ///< pack size & status into boundary tag
#define SIZE(v)            (v & SIZE_MASK)             ///< extract size from boundary tag
#define STATUS(v)          (v & STATUS_MASK)           ///< extract status from boundary tag

#define GET(p)             (*(TYPE*)(p))               ///< read word at *p
#define GET_SIZE(p)        (SIZE(GET(p)))              ///< extract size from header/footer
#define GET_STATUS(p)      (STATUS(GET(p)))            ///< extract status from header/footer

#define PUT(p,v)           (*(TYPE*)(p) = (v))         ///< write value v to dereference pointer p
#define HDR2FTR(p)         ((p)+GET_SIZE(p)-TYPE_SIZE) ///< get location of footer tag given header tag

#define NEXT_BLOCK(p)       ((p)+GET_SIZE(p))           ///< get pointer to next block of p
#define PREV_BLOCK(p)       ((p)-GET_SIZE((p)-TYPE_SIZE))

// TODO add more macros as needed

/// @brief print a log message if level <= mm_loglevel. The variadic argument is a printf format
///        string followed by its parametrs
#define LOG(level, ...) mm_log(level, __VA_ARGS__)

/// @brief print a log message. Do not call directly; use LOG() instead
/// @param level log level of message.
/// @param ... variadic parameters for vprintf function (format string with optional parameters)
static void coalesce(void* block);
static void mm_log(int level, ...)
{
  if (level > mm_loglevel) return;

  va_list va;
  va_start(va, level);
  const char *fmt = va_arg(va, const char*);

  if (fmt != NULL) vfprintf(stdout, fmt, va);

  va_end(va);

  fprintf(stdout, "\n");
}


/// @brief print error message and terminate process. The variadic argument is a printf format
///        string followed by its parameters
#define PANIC(...) mm_panic(__func__, __VA_ARGS__)

/// @brief print error message and terminate process. Do not call directly, Use PANIC() instead.
/// @param func function name
/// @param ... variadic parameters for vprintf function (format string with optional parameters)
static void mm_panic(const char *func, ...)
{
  va_list va;
  va_start(va, func);
  const char *fmt = va_arg(va, const char*);

  fprintf(stderr, "PANIC in %s%s", func, fmt ? ": " : ".");
  if (fmt != NULL) vfprintf(stderr, fmt, va);

  va_end(va);

  fprintf(stderr, "\n");

  exit(EXIT_FAILURE);
}

static void* extend_heap(size_t words){
  void* bp_head;
  void* heap_start_ex;
  void* bp;
  size_t extend_size = (words/ds_getpagesize()+1)*ds_getpagesize();
  if((bp_head = ds_sbrk(CHUNKSIZE))==(void*)-1) PANIC("Cannot increase heap anymore");
  bp = ds_sbrk(0);
  LOG(2, "extend heap : break is now at %p", bp);

  heap_end = PTR((WORD(bp)-TYPE_SIZE)/BS*BS);
  //PUT(bp-TYPE_SIZE, PACK(extend_size, FREE));
  //PUT(bp+extend_size-TYPE_SIZE, PACK(extend_size, FREE));
  //PUT(NEXT_BLOCK(bp)-TYPE_SIZE, PACK(0, ALLOC));
  heap_start_ex = PTR((WORD(bp_head)+TYPE_SIZE+BS-1)/BS*BS);

  PUT(heap_start_ex-TYPE_SIZE, PACK(extend_size, FREE));
  PUT(heap_end, PACK(extend_size, FREE));

  //PUT(NEXT_BLOCK(bp), PACK(0,ALLOC));
//  TYPE size = heap_end-heap_start;
//  TYPE bdrytag = PACK(size, FREE);

//  PUT(heap_start, bdrytag);
//  PUT(heap_end-TYPE_SIZE, bdrytag);
  coalesce(bp_head+TYPE_SIZE);
  LOG(2, "coalesced block size : %d", GET_SIZE(bp));
  return bp;
}

static void* ff_get_free_block(size_t);
static void* nf_get_free_block(size_t);
static void* bf_get_free_block(size_t);

void mm_init(AllocationPolicy ap)
{
  LOG(1, "mm_init(%d)", ap);
  
  //set allocation policy
  char *apstr;
  switch (ap){
    case ap_FirstFit : get_block = ff_get_free_block; apstr = "first fit"; break;
    case ap_NextFit : get_block = nf_get_free_block; apstr = "next fit"; break;
    case ap_BestFit : get_block = bf_get_free_block; apstr = "best fit"; break;
    default : PANIC("Invalid allocation policy");
  }
  LOG(2, "  allocation policy       %s\n", apstr);

  //
  // retrieve heap status and perform a few initial sanity checks
  //
  ds_heap_stat(&ds_heap_start, &ds_heap_brk, NULL);
  PAGESIZE = ds_getpagesize();

  LOG(2, "  ds_heap_start    %p\n"
         "  ds_heap_brk      %p\n"
         "  PAGESIZE         %d\n",
         ds_heap_start, ds_heap_brk, PAGESIZE);

  if (ds_heap_start == NULL) PANIC("Data segment not initialized.");
  if (ds_heap_start != ds_heap_brk) PANIC("Heap not clean.");
  if (PAGESIZE == 0) PANIC("Reported pagesize == 0.");

  //
  // initialize heap
  //
  // TODO

  void* temp_bf;
  LOG(2, "Get first block of memory for heap");
  if((temp_bf = ds_sbrk(CHUNKSIZE))==(void*)-1) PANIC("Cannot increase heap break"); //increase heap_brk
  ds_heap_brk = ds_sbrk(0);

  LOG(2, "heap_start : %p, ds_sbrk : %p", ds_heap_start,temp_bf); 
  LOG(2, "break is now at %p", ds_heap_brk);

  heap_start = PTR((WORD(ds_heap_start)+TYPE_SIZE+BS-1)/BS*BS);
  heap_end = PTR((WORD(ds_heap_brk)-TYPE_SIZE)/BS*BS);

  LOG(2, "heap start at %p\n"
      "heap end at %p\n",
      heap_start, heap_end);

  TYPE F = PACK(0, ALLOC);
  PUT(heap_start-TYPE_SIZE, F);

  TYPE H = PACK(0, ALLOC);
  PUT(heap_end, H);

  TYPE size = heap_end - heap_start;
  TYPE bdrytag = PACK(size, FREE);

  PUT(heap_start, bdrytag);
  PUT(heap_end-TYPE_SIZE, bdrytag);
  //
  // heap is initialized
  //
  mm_initialized = 1;
}


static void* nf_get_free_block(size_t size){
  LOG(1, "nf_get_free_block(0x%lx (%lu))", size, size);
  assert(mm_initialized);

  void* block;
  //next fit : start at prev ends
  //if next block is null then just do first fit
  if(next_block == NULL) block = heap_start;
  else block = next_block;

  size_t bsize, bstatus;
  LOG(2, "starting search at %p", block);
  do{
    bstatus = GET_STATUS(block);
    bsize = GET_SIZE(block);
    LOG(2, "  %p: size: %lx(%lu), status : %s",
        block, bsize, bsize, bstatus == ALLOC?"Allocated": "free");
    if((bstatus == FREE) &&(bsize>=size)){
      //found block
      LOG(2, "  ->match");
      next_block = block;
      return block;
    }
    block += bsize;
  }while(GET_SIZE(block)>0);

  //cannot find any block
  LOG(2, "  no suitable block found");
  return NULL;
}

static void* bf_get_free_block(size_t size){
  LOG(1, "bf_get_free_block(0x%lx (%lu))", size, size);
  assert(mm_initialized);
  int flag = 0;

  //best fit : start at beginning of the heap
  void *block = heap_start;
  size_t bsize, bstatus, min;
  LOG(2, "starting search at %p", block);
  int cnt = 0;
  int mincnt = 0;
  bsize = GET_SIZE(block);
  //min = bsize;
  do{
    bstatus = GET_STATUS(block);
    bsize = GET_SIZE(block);
    LOG(2, "  %p : size: %lx(%lu), status : %s",
      block, bsize, bsize, bstatus == ALLOC? "Allocated" : "free");
    cnt++;
    //is block free & big enough?
    if((bstatus == FREE) && (bsize >= size)){
      //found block
      LOG(2, "  ->match, store");
      if(!flag){
        min = bsize;
        mincnt = cnt;
        flag = 1;
      }
      else if(flag ==1 && min>=bsize) {
          min = bsize;
          mincnt = cnt;
      }
    }
    //if it's not free and so small, get next block
    block += bsize;
    //bsize = GET_SIZE(block);
    LOG(2, "min count : %d, cnt : %d", mincnt, cnt);

  } while(GET_SIZE(block)>0); // only sentinel size ==0
  block = NULL;
  LOG(2, "outside the do while loop");

  if(mincnt>0){
    block = heap_start;
    for(int i = 1;i<=mincnt;i++){
      bsize = GET_SIZE(block);
      if(i==mincnt) return block;
      LOG(2, "bsize : %d", bsize);
      block += bsize;
    }
  }
  else LOG(2, "  no suitable block found");
  return block;
}

static void* ff_get_free_block(size_t size){

  LOG(1, "ff_get_free_block(0x%lx (%lu))", size, size);
  assert(mm_initialized);

  //first fit : start at beginning of the heap
  void *block = heap_start;
  size_t bsize, bstatus;
  LOG(2, "starting search at %p", block);
  do{
    bstatus = GET_STATUS(block);
    bsize = GET_SIZE(block);

    LOG(2, "  %p : size: %lx(%lu), status : %s",
      block, bsize, bsize, bstatus == ALLOC? "Allocated" : "free");

    //is block free & big enough?
    if((bstatus == FREE) && (bsize >= size)){
      //found block
      LOG(2, "  ->match");
      return block;
    } 

    //if it's not free and so small, get next block
    block += bsize;

  } while(GET_SIZE(block)>0); // only sentinel size ==0

  LOG(2, "  no suitable block found");
  return NULL;
}

static void coalesce(void* block){
  LOG(1, "coalesce(%p)", block);

  assert(mm_initialized);
  assert(GET_STATUS(block)==FREE);

  TYPE size = GET_SIZE(block);
  void *hdr = block;
  void *footer = HDR2FTR(block);

  //can we coalesce with following block or not?
  //we need to check the next pointer
  if(GET_STATUS(NEXT_BLOCK(block))== FREE){
    //coalesce
    LOG(2, "  coalescing with succeeding block");

    //size of coalesced block : size of block + size of following block
    size += GET_SIZE(NEXT_BLOCK(block));
    //compute new location of footer tag of colaesced block
    footer = hdr + size - TYPE_SIZE;
  }
  if(GET_STATUS(PREV_BLOCK(block))==FREE){
    LOG(2, "  coalescing with succeding block");
    
    //size of coalesced block : size of block + size of following block
    size += GET_SIZE(PREV_BLOCK(block));
    //compute new location of footer tag of colaesced block
    hdr = PREV_BLOCK(block);
  }

  if(size>GET_SIZE(block)){
    PUT(hdr, PACK(size, FREE));
    PUT(footer, PACK(size, FREE));
  }
}

void* mm_malloc(size_t size)
{
  LOG(1, "mm_malloc(0x%lx (%lu))", size, size);

  assert(mm_initialized);

  // header // payload in the middle
  size_t blocksize = ROUND_UP(TYPE_SIZE + size+TYPE_SIZE); // print the size of the block
  LOG(2, "  blocksize :   %lx (%lu))", blocksize, blocksize);
  //
  // TODO
  //
  // find free block
  void *block = get_block(blocksize);
  LOG(2, "  got free block: %p", block);

  // TODO
  if(block==NULL){
    // no free block is big enough -> expand heap
    size_t temp_size = MAX(CHUNKSIZE, blocksize);
    if((block = extend_heap(temp_size))==NULL){
      return NULL;
    }
    //LOG(2, "  expand_heap not implemented");
    //return block;
  }

  // spliting!
  // split block if block is larger than we requested
  size_t bsize = GET_SIZE(block);
  if(blocksize < bsize){
    // make header and footer
    LOG(2, "blocksize %d < bsize %d", blocksize, bsize);
    void *next_block = block+blocksize; //not block+bsize
    size_t next_size = bsize-blocksize;

    PUT(next_block, PACK(next_size, FREE)); // header of next_block
    //block+bsize-TYPE_SIZE also works
    PUT(next_block+next_size-TYPE_SIZE, PACK(next_size, FREE)); // footer of next_block
  }

  LOG(2, "blocksize %d> bsize %d", blocksize, bsize);
  PUT(block, PACK(blocksize, ALLOC));
  PUT(block+blocksize-TYPE_SIZE, PACK(blocksize, ALLOC));

  // return block to payload!
  return block+TYPE_SIZE;
}

void* mm_calloc(size_t nmemb, size_t size)
{
  LOG(1, "mm_calloc(0x%lx, 0x%lx)", nmemb, size);

  assert(mm_initialized);

  //
  // calloc is simply malloc() followed by memset()
  //
  void *payload = mm_malloc(nmemb * size);

  if (payload != NULL) memset(payload, 0, nmemb * size);

  return payload;
}

void* mm_realloc(void *ptr, size_t size)
{
  LOG(1, "mm_realloc(%p, 0x%lx)", ptr, size);

  assert(mm_initialized);

  //
  // TODO (optional)
  //

  return NULL;
}

void mm_free(void *ptr)
{
  LOG(1, "mm_free(%p)", ptr);

  assert(mm_initialized);

  //
  // TODO
  //
  void *block = ptr-TYPE_SIZE;
  //check whether block is allocated
  if(GET_STATUS(block)!=ALLOC){
    LOG(1, "  WARNING : double-free detected");
    return;
  }

  // so block is allocated!
  TYPE size = GET_SIZE(block);
  PUT(block, PACK(size, FREE));
  PUT(block+size-TYPE_SIZE, PACK(size, FREE));

  // colaesce when there are two free block next to each other
  coalesce(block); // check just before and after the block
}


void mm_setloglevel(int level)
{
  mm_loglevel = level;
}


void mm_check(void)
{
  assert(mm_initialized);

  void *p;

  printf("\n----------------------------------------- mm_check ----------------------------------------------\n");
  printf("  ds_heap_start:          %p\n", ds_heap_start);
  printf("  ds_heap_brk:            %p\n", ds_heap_brk);
  printf("  heap_start:             %p\n", heap_start);
  printf("  heap_end:               %p\n", heap_end);
  printf("\n");
  p = PREV_PTR(heap_start);
  printf("  initial sentinel:       %p: size: %6lx, status: %lx\n", p, GET_SIZE(p), GET_STATUS(p));
  p = heap_end;
  printf("  end sentinel:           %p: size: %6lx, status: %lx\n", p, GET_SIZE(p), GET_STATUS(p));
  printf("\n");
  printf("  blocks:\n");

  long errors = 0;
  p = heap_start;
  while (p < heap_end) {
    TYPE hdr = GET(p);
    TYPE size = SIZE(hdr);
    TYPE status = STATUS(hdr);
    printf("    %p: size: %6lx, status: %lx\n", p, size, status);

    void *fp = p + size - TYPE_SIZE;
    TYPE ftr = GET(fp);
    TYPE fsize = SIZE(ftr);
    TYPE fstatus = STATUS(ftr);

    if ((size != fsize) || (status != fstatus)) {
      errors++;
      printf("    --> ERROR: footer at %p with different properties: size: %lx, status: %lx\n", 
             fp, fsize, fstatus);
    }

    p = p + size;
    if (size == 0) {
      printf("    WARNING: size 0 detected, aborting traversal.\n");
      break;
    }
  }

  printf("\n");
  if ((p == heap_end) && (errors == 0)) printf("  Block structure coherent.\n");
  printf("-------------------------------------------------------------------------------------------------\n");
}
