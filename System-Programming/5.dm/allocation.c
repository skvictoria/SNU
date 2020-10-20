#include <stdio.h>
#include <stdlib.h>

void foo(int n, int m){

  int *p;

  p = (int*) malloc(n*sizeof(int));
  if(p==NULL){
    perror("malloc");
    exit(EXIT_FAILURE);
  }

  for(int i=0; i<n; i++){
    p[i] = i;
  }



}
