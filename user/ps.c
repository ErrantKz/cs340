#include "kernel/types.h"
#include "kernel/param.h"
#include "user/user.h"

int main(){
    struct pinfo infos[NPROC];
    if(getpinfo(infos)<0){
       printf("getpinfo failed.\n");
       exit(-1);
    }
    printf("PID\tPNAME\tPRI\tTICKS_PRIT1\tTICKS_PRIT2\n");
    for(int i=0;i<NPROC;i++){
        if(infos[i].pid>0){
           printf("%d\t%s\t%d\t%d\t\t%d\t\n",infos[i].pid,infos[i].name,infos[i].priority,infos[i].ticks_1,infos[i].ticks_2);
        }
    }
    exit(0);
}
