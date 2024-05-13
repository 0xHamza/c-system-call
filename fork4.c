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
        printf("pid = %d cocuk surec\n",pid);
    else
        printf("pid = %d ana surec\n",pid);

    printf("--->pid = %d \n",pid);

    return 0;
}