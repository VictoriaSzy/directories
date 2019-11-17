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
      //printf("%s\n", item->d_name) ;
      s += individual.st_size ;
    }
    item = readdir(dir) ;
  }
  closedir(dir) ;
  return s ; // this is our size of the directory
}

void list_dirs() {
  DIR * d = opendir(".");
  struct dirent * item = readdir(d) ;
  while (item) {
    if (item->d_type == DT_DIR) printf("\t%s\n", item->d_name) ;
    item = readdir(d) ;
  }
  closedir(d) ;
}

void list_files() {
  // only prints
  DIR * d = opendir(".") ; // current directory
  struct dirent * item = readdir(d) ;
  while (item) {
    if (item->d_type == DT_REG) printf("\t%s\n", item->d_name) ;
    item = readdir(d) ;
  }
  closedir(d) ;
}

int main() {
  printf("\nStatistics for directory: .\n") ;
  printf("Total directory size: %d Bytes\n", dir_size()) ;
  printf("\nDirectories:\n") ;
  list_dirs() ;
  printf("\nFiles:\n") ;
  list_files() ;
  return 0 ;
}
