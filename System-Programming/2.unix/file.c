#define _GNU_SOURCE
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#define DEFAULT_CHARS 128
#define CHARS_PER_LINE 16
int main(int argc, char *argv[])
{
  int fd, i, n;
  unsigned char c;
  //
  // check arguments
  //
  if(argc<2){
    fprintf(stderr, "Usage:%s<filename>\n", argv[0]);
    fprintf(stderr, "(use '-' for stdin)\n");
    return EXIT_FAILURE;
  }

  //if 2nd letter is - then fd = stdin_fileno
  if(strcmp(argv[1], "-")==0) fd = STDIN_FILENO;
  //else if 
  else if((fd=open(argv[1], O_RDONLY))==-1){
    perror("Cannot open file");
    return EXIT_FAILURE;
  }
  //number of characters to dump
  n = DEFAULT_CHARS;// n=128
  if(argc>=3){
    n = atoi(argv[2]);
  }

  //read and dump n char from file
  i = 0;
  printf("%04d: ", i);

  while(i<n){
    //
    int r = read(fd, &c, sizeof(c));
    if(r == sizeof(c)){
      i++;
      if(c<32) printf("<%02x>", c);
      else printf("%c", c);

      if(i%CHARS_PER_LINE==0){
        printf("\n");
        if(i<n) printf("%04d: ", i);
      }
    }
    else{
      fprintf(stderr, "\n Error Reading file ( pos: %d).\n",i);
      break;
    }
  }
  if(i%CHARS_PER_LINE>0) printf("\n");
  close(fd);
  return EXIT_SUCCESS;
}
