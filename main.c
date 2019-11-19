#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <dirent.h>

int dir_size() {
  DIR * dir = opendir(".") ;
  struct dirent * item = readdir(dir) ;
  int s = 0 ;
  struct stat individual ;
  while (item) {
    if (item->d_type == DT_REG) {
      stat(item->d_name, &individual) ;
      s += individual.st_size ;
    }
    item = readdir(dir) ;
  }
  closedir(dir) ;
  return s ; // this is our size of the directory
}

void list_dirs() {
  DIR * d = opendir(".") ;
  struct dirent * item = readdir(d) ;
  while (item) {
    if (item->d_type == DT_DIR) printf("\t%s\n", item->d_name) ;
    item = readdir(d) ;
  }
  closedir(d) ;
}

void list_files() {
  DIR * d = opendir(".") ; // current directory
  struct dirent * item = readdir(d) ;
  while (item) {
    if (item->d_type == DT_REG) printf("\t%s\n", item->d_name) ;
    item = readdir(d) ;
  }
  closedir(d) ;
}

int main(int argc, char * argv[]) {
  char * dir = malloc(100) ;
  if (argc < 2) {
    printf("\nPlease enter the name of the directory you want to scan: \n") ;
    fgets(dir, 100, stdin) ;
    dir[strlen(dir) - 1] = 0 ;
  }
  else {
    // otherwise we have the name of the directory the user wants to look at so it's good
    dir = argv[1] ;
  }
  DIR * d = opendir(dir) ;
  if (errno) {
    printf("\nThere is some sort of error with OPENING the directory...\n") ;
    printf("\nerrno returned this: %d \nDUE TO:\n", errno) ;
    printf("%s\n", strerror(errno)) ;
    return 0 ; // we will not go any further with running this!
  }
  printf("\nStatistics for directory: %s\n", dir) ;
  struct dirent * f = readdir(d) ;
  if (errno) {
    printf("\nThere is some sort of error with READING the directory...\n") ;
    printf("\nerrno returned this: %d \nDUE TO:\n", errno) ;
    printf("%s\n", strerror(errno)) ;
    return 0 ; // we will not go any further with running this!
  }
  struct stat b ;
  int s = 0 ; // now we can start finding the size
  while (f) {
    stat(f->d_name, &b) ;
    s += b.st_size ;
    f = readdir(d) ; // move on to next file in directory to see if it's a file or directory!
  }
  printf("Total Directory Size: %d bytes\n", s) ;
  rewinddir(d) ;
  f = readdir(d) ;
  printf("\nDirectories: \n") ;
  while (f) {
    if (f->d_type == DT_DIR) {
      printf("\n\t%s", f->d_name) ;
    }
    f = readdir(d) ;
  }
  rewinddir(d) ;
  f = readdir(d) ;
  printf("\n\nFiles:\n") ;
  while (f) {
    if (f->d_type == DT_REG) {
      printf("\n\t%s", f->d_name) ;
    }
    f = readdir(d) ; // move on to what's next in this directory
  }
  printf("\n") ;
  
  return 0 ;
}
