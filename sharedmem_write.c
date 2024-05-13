#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

int main(){

    void *shared_memory;  
    int shmid;  
    shmid=shmget((key_t)2345, 1024, 0666|IPC_CREAT);   
    shared_memory=shmat(shmid,NULL,0);   

    pid_t pid;
    pid = fork();

    if(pid==0)//COCUK SUREC
    { 
        wait(NULL); //ANNE SURECIN BITMESINI BEKLETIYOR ZORUNLU DEGIL, SIRAYLA CALISMALARI ICIN
        int CocukKendiPidi = getpid();
        sprintf(shared_memory, "%d", CocukKendiPidi);  //MESAJ BELLEGE YOLLANIR

    }else if(pid > 0)//ANNE SUREC
    { 
        printf("Cocuk Pid = %d \n",pid);
        printf("Anne Pid = %d \n",getpid());
        
    }else{
        printf("ERROR");
    }

    return 0;
}