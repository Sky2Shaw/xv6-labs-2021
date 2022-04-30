/* 
    Use pipe to create a pipe.
    Use fork to create a child.
    Use read to read from the pipe, and write to write to the pipe.
    Use getpid to find the process ID of the calling process.
    Add the program to UPROGS in Makefile.
    User programs on xv6 have a limited set of library functions available to them. You can see the list in user/user.h; the source (other than for system calls) is in user/ulib.c, user/printf.c, and user/umalloc.c. 
*/

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  if(argc != 1){
    fprintf(2, "Usage: pingpong...\n");
    exit(1);
  }
  char buff[1] = { 0 };
  int p1[2];
  int p2[2];
  pipe(p1);
  pipe(p2);
  if (fork() == 0) {
      close(p1[1]);
      if (read(p1[0], buff, sizeof(buff)) > 0) {
          printf("%d: received ping\n", getpid());
          close(p1[0]);
          
          close(p2[0]);
          write(p2[1], "", 1);
          close(p2[1]);
      }
  } else {
    close(p1[0]);
    write(p1[1], "", 1);
    close(p1[1]);
    
    close(p2[1]);
    if (read(p2[0], buff, sizeof(buff)) > 0) {
        printf("%d: received pong\n",  getpid());
        close(p2[0]);

    }
    exit(0);
  }
  


  exit(0);
}
