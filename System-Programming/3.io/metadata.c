#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>

int main(int argc, char* argv[]){
  DIR *dir = opendir(argc>1? argv[1]: ".");
  if(dir==NULL){
    perror("Cannot open directory");
    return EXIT_FAILURE;
  }
  //int dd = dirfd(dir);

  struct dirent* e;
  int errno = 0;
  while((e=readdir(dir))!=NULL){
    struct stat sb;
    char temp[100];
    sprintf(temp, "%s%s", argv[1], e->d_name);
    //printf("argv: %s\n", argv[1]);
    //temp = strcat(temp, e->d_name);
    //printf("%s\n", temp);
    if(stat(temp, &sb)<0){
      perror("Cannnot stat file");
    }
    else{
      printf("  %-32s %10ld\n", e->d_name, sb.st_size);
    }
    errno = 0;
    
  }
  if(errno!=0) perror("Cannot enumerate Directory");
  closedir(dir);
  return EXIT_SUCCESS;
}
