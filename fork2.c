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

    return 0;
}