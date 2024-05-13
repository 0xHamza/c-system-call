#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
int main()
{
    pid_t pid_f1, pid_f2;

    printf("\n");
    pid_f1 = fork();
    pid_f2 = fork();

    if(pid_f1 == 0)
    {
        printf("COCUK pid_f1:%d\n",getpid()); 
    }else{
        wait(NULL);
        printf("ANA pid_f1:%d\n",getpid());
    }

    printf("SON\n");

    return 0;
}

/*

Double Fork:

Kod, arka arkaya pid_f1 ve pid_f2 olmak üzere iki çatal oluşturur. Bu, programın toplam dört süreç oluşturacağı anlamına gelir: orijinal ana süreç ve üç çocuk süreç.

İşte olanlar:

İlk fork() bir çocuk süreç oluşturur ve pid_f1 çocuk süreçte 0'a ve ana süreçte çocuk sürecin süreç kimliğine ayarlanır.
İkinci fork(), 1. adımda oluşturulan hem ana hem de alt süreçlerden başka bir alt süreç oluşturur. Bu, şu anda dört süreç olduğu anlamına gelir: orijinal ana süreç, ilk çocuk süreç ve ikinci fork() tarafından oluşturulan iki yeni çocuk süreç.
Şimdi çıktıyı analiz edelim:

ANA pid_f1:8214 ve ANA pid_f1:8211 iki ana süreç (orijinal ana süreç ve ilk çocuk süreç) tarafından yazdırılır. Üst süreçteki wait(NULL) çağrısı, üst sürecin mesajı yazdırmadan önce alt sürecin bitirmesini beklemesini sağlar.
COCUK pid_f1:8212 ve COCUK pid_f1:8213, ikinci fork() tarafından oluşturulan iki çocuk süreç tarafından yazdırılır.
SON mesajı dört süreç tarafından da yazdırılır, bu yüzden çıktıda dört kez görünür.

Yazdırılan süreç kimlikleri, mesajları yazdıran süreçlerin kimlikleridir. Süreçler eşzamanlı olarak çalıştığı için çıktıların sırası garanti edilmez.

hamza@DESKTOP-FE4MRVU:~/isletim/zombi$ gcc -o soru2 soru2_doublefork.c
hamza@DESKTOP-FE4MRVU:~/isletim/fork$ ./soru2

Ekran ciktisi:

ANA pid_f1:8214
SON
ANA pid_f1:8211
SON
COCUK pid_f1:8212
SON
COCUK pid_f1:8213
SON
*/