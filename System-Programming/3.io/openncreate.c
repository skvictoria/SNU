#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]){

  int fd;
  unsigned char c;
  fd = creat(argv[1], S_IRUSR|S_IWUSR);

  if(open(argv[1], O_RDONLY)<0){
    perror("Cannot open file");
    exit(EXIT_FAILURE);
  }
  else{
    read(STDIN_FILENO, &c, sizeof(c));
    write(fd, &c, sizeof(c));
  }
  return EXIT_SUCCESS;
}

