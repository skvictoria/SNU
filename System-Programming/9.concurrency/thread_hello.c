#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void* thread(void *vargp){
  sleep(1);
  printf("Hello thread\n");
  sleep(5);
  return NULL;
}

int main(int argc, char *argv[]){
  int err;
  pthread_t tid;

  if((err = pthread_create(&tid, NULL, thread, NULL))!=0){
    perror(strerror(err));
  }

  printf("main trhread wiating\n");
  if((err = pthread_join(tid, NULL))!=0) perror(strerror(err));

  printf("thread has joined \n");
  return EXIT_SUCCESS;
}
