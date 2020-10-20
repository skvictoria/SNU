#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>

pid_t pid;

void f(void)
{
  printf("{A}\n");
}

void g(void)
{
  printf("{B}\n");
}

void h(int sig)
{
  printf("{C}\n");
  kill(pid, SIGUSR1);
}

void i(int sig)
{
  printf("{D}\n");
  exit (0);
}

int main() {
  signal(SIGUSR1, h);
  printf("1\n");
  atexit(g);
  printf("2\n");

  printf("3\n");

  if ((pid = fork()) == 0) {
    printf("4\n");
    signal(SIGUSR1, i);
    printf("5\n");
    kill(getppid(), SIGUSR1);
    printf("6\n");
    while (1) {printf("7\n");}
  } else {
    printf("8\n");
    atexit(f);
    printf("9\n");
    waitpid(pid, NULL, 0);
    printf("10\n");
  }
  printf("11\n");
  
}
