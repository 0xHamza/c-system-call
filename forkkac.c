#include <stdio.h>
#include<sys/types.h>
#include<unistd.h>

int main(){

    printf("Soru: Fork çalışınca kaç kere çalışır: her bir satır 2^n, 2^forkSayisi kadar calisir\n");

    if(1){
        printf("2)fork oncesi\n");

        fork();
        printf("3)fork sonrası\n");
    }
    printf("4)fork sonrası\n");

    printf("Exit program.\n");
    return 0;
}

/*
hamza@DESKTOP-FE4MRVU:~/isletim/fork$ gcc -o forkkac2 forkkac.c
hamza@DESKTOP-FE4MRVU:~/isletim/fork$ ./forkkac2

Soru: Fork çalışınca kaç kere çalışır: her bir satır 2^n, 2^forkSayisi kadar calisir
2)fork oncesi
3)fork sonrası
4)fork sonrası
Exit program.
3)fork sonrası
4)fork sonrası
Exit program.

*/