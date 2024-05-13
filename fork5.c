#include <stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include <sys/wait.h>
int main()
{
    pid_t pid;

    printf("1)fork oncesi\n");
    
    pid = fork();
    
    //printf("2)fork sonrası\n");

    if(pid==0)//COCUK SUREC
    {
        wait(NULL); //ANNE SURECIN BITMESINI BEKLETIYOR
        printf("----> pid = %d cocuk surec\n",pid);
        printf("cocuk surecin pid degeri = %d \n", getpid());//COCUK -> 1022
        printf("cocuk surecin ppid degeri = %d \n",getppid());//ANNESI -> 1021
    }else if(pid > 0) //ANNE SUREC
    {
        printf("----> pid = %d ana surecte gelen pid Cocuga Aittir!\n",pid); //COCUK PIDI
        printf("ana surecin get pid degeri = %d \n",getpid());//ANA SURECIN -> 1021
        printf("ana surecin get ppid degeri = %d \n",getppid());//ANA SURECI ILK GELEN BAŞLATAN -> 218
    }else{
        printf("ERROR");
        printf("----> pid = %d ERROR \n",pid); //COCUK 
    }
    
    

    return 0;
}