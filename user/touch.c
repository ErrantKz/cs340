#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"

int main(int argc,char* argv[]){
    if(argc<2) printf("failed.\n");
    int fd=open(argv[1],O_CREATE);
    close(fd);
    exit(0);
}
