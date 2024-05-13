#include <stdio.h>
#include<sys/types.h>
#include<unistd.h>

int main(){
    
    printf("1)fork oncesi\n");
    
    fork();
    printf("2)fork sonrası\n");

    return 0;
}