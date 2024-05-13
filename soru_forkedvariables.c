#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    int a=20, pid;

    printf("a'nin baslangic degeri: %d \n",a);
   
    pid = fork();
    
    if(pid==0)
    {
        a=a-10;
        printf("c = %d cocuk surec\n",a); 
    }else
    {
        a=a+10;
        printf("p = %d ana surec\n",a);
    }
    return 0;
}


/*

Forked Variables:

Çıktının nedeni fork() işlevinin çalışma şeklinden kaynaklanmaktadır. fork() çağrıldığında, mevcut süreci (ana süreç) çoğaltarak yeni bir süreç (alt süreç) oluşturur. Çocuk süreç, değişkenlerin değerleri de dahil olmak üzere ebeveynin bellek alanının bir kopyasını alır.

Bu kodda fork(), a 20 olarak başlatıldıktan sonra çağrılır. Alt süreç, a'nın 20 değerine sahip bir kopyasını alır. Daha sonra, alt süreçte a değeri 10 azaltılır, böylece a değeri 10 olur. Üst süreçte, a 10 artırılır, böylece a 30 olur.

Çıktı, hem üst hem de alt süreçlerdeki a değerlerini gösterir. Ana ve alt süreçler eşzamanlı olarak çalıştığı için çıktının sırası garanti edilmez.

Ekran Ciktisi:
hamza@DESKTOP-FE4MRVU:~/isletim/fork$ gcc -o soru soru_forkedvariables.c
hamza@DESKTOP-FE4MRVU:~/isletim/fork$ ./soru
a'nin baslangic degeri: 20 
p = 30 ana surec
c = 10 cocuk surec

*/