#include "kernel/types.h"
#include "user/user.h"

int main(){
    int p2c1[2],c2p1[2];
    int p2c2[2],c2p2[2];
    int buffer[4];

    pipe(p2c1);
    pipe(c2p1);
    pipe(p2c2);
    pipe(c2p2);

    int pid1=fork();
    if(pid1==0){
       close(p2c1[1]);
       close(c2p1[0]);
       read(p2c1[0],buffer,4);
       printf("%d: pong\n",getpid());
       write(c2p1[1],"ACK",3);
       close(p2c1[0]);
       close(c2p1[1]);
       exit(0);
    }
    int pid2=fork();
    if(pid2==0){ 
       close(p2c2[1]);
       close(c2p2[0]);
       read(p2c2[0],buffer,4);
       printf("%d: pong\n",getpid());
       write(c2p2[1],"ACK",3);
       close(p2c2[0]);
       close(c2p2[1]);
       exit(0);
    }
    close(p2c1[0]);
    close(c2p1[1]);
    close(p2c2[0]);
    close(c2p2[1]);
    write(p2c1[1],"ACK",3);
    write(p2c2[1],"ACK",3);

    char ack[4];
    read(c2p1[0],ack,3);
    read(c2p2[0],ack,3);
    close(p2c1[1]);
    close(c2p1[0]);
    close(p2c2[1]);
    close(c2p2[0]);
    wait(0);
    wait(0);
    exit(0);
}
