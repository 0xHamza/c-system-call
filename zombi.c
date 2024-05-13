/*

Kodun Ekran Ciktisi
hamza@DESKTOP-FE4MRVU:~/isletim/zombi$ gcc -o zombi zombi.c
hamza@DESKTOP-FE4MRVU:~/isletim/zombi$ ./zombi
pid = 3789 ana surec
0) pid = 0 cocuk surec
1) pid = 0 cocuk surec
2) pid = 0 cocuk surec
3) pid = 0 cocuk surec
4) pid = 0 cocuk surec
5) pid = 0 cocuk surec
6) pid = 0 cocuk surec
7) pid = 0 cocuk surec
8) pid = 0 cocuk surec
9) pid = 0 cocuk surec
10) pid = 0 cocuk surec
11) pid = 0 cocuk surec
12) pid = 0 cocuk surec
13) pid = 0 cocuk surec
14) pid = 0 cocuk surec
15) pid = 0 cocuk surec
16) pid = 0 cocuk surec
17) pid = 0 cocuk surec
18) pid = 0 cocuk surec
19) pid = 0 cocuk surec
..
..


*/

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    int i;
    pid_t pid;
    pid = fork();

    if (pid == 0)
    {
        for (i = 0; i < 20; i++)
            printf("%d) pid = %d cocuk surec\n", i, pid);
    }
    else       // Bu durumda, oluşturulan "child process"in kimliğini yazdırır ve sonsuz bir döngüye girer.
    { 
        printf("pid = %d ana surec\n", pid);
        while (1)
        {
            /* code */
        }
    }
    return 0;
}