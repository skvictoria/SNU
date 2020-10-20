#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char global[1024*1024];

int main(int argc, char *argv[]){
  char *ptr = malloc(1024*1024);
  printf("Hello world");

  printf("  address of main :   %p\n", main);
  printf("  address of printf:  %p\n", printf);

  printf("  address of global :   %p\n", global);

  printf("  address of ptr :   %p\n", &ptr);
  printf("  address of mem[ptr] :   %p\n", ptr);

  while(1) sleep(1);
  //free(ptr);

  return EXIT_SUCCESS;
}
