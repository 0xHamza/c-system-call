#include<stdio.h> 
#include<unistd.h> 
int main(int argc,char *argv[]){

    printf("A \n");
    fork();
    printf("B \n");
    fork();
    printf("C \n");

    return 0;
}

/*
Ekran ciktisi:
A 
B 
B 
C 
C 
C 
C 
*/