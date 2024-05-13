#include <stdio.h>

#include<sys/types.h>

#include<unistd.h>


int main()

{
    pid_t pid;

    printf("1)fork oncesi\n");
    //fork();
    
    pid = fork();
    
    printf("2)fork sonrası\n");

    if(pid==0)
        printf("0-cocuk surec\n");
    else if(pid >0 )
        printf("!0-ana surec\n");
    else
        printf("hata çıktı");
        
    printf("pid = %d \n",pid);

    return 0;
}