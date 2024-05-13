#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main()
{
    pid_t pid;
    printf("1) Fork oncesi\n");
    
    pid = fork();
    
    printf("2) Fork sonrası\n");

    if(pid==0)
    {
        execlp("/bin/ls","ls",NULL); //EXEC'E DEN SONRAKI KISIM(COCUKLA ALAKALI KISIM) CALISMAZ
        printf("COCUK - pid = %d\n",pid); 
    }else{
        wait(NULL); //COCUK SURECIN BITMESINI BEKLETIYOR
        printf("ANA - pid = %d\n",pid);
    }
    
    printf("SON - pid = %d \n",pid);

    return 0;
}