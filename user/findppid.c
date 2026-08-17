#include "kernel/types.h"
#include "user/user.h"

void create_children(int n);
int main(int argc,char* argv[]){
    if(argc<2) printf("failed.\n");
    int n=atoi(argv[1]);
    if(n<=0) exit(1);
    create_children(n);
    exit(0);
}

void create_children(int n){
    if(n<=0) return;
    int pid=fork();
    if(pid==0){
       create_children(n-1);
       printf("my ID is %d, my parent ID is %d\n",getpid(),getppid());
       exit(0);
    }
    else wait(0);
}
