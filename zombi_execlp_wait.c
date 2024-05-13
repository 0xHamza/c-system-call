/*
## Teorik Bilgiler

### Fork Sistem Çağrısı

* `fork()` sistem çağrısı, mevcut işlemin bir kopyasını oluşturur.
* Yeni oluşturulan işlem, **çocuk işlem** olarak adlandırılır.
* Ana işlem, **ebeveyn işlem** olarak adlandırılır.
* Çocuk işlem, ebeveyn işlemin tam bir kopyasıdır. Aynı bellek alanını, açık dosyaları ve diğer kaynakları paylaşırlar.
* `fork()` çağrısı başarılı olursa, ebeveyn işleme çocuğun işlem kimliği (PID) döndürür. Çocuk işleme ise 0 değeri döndürülür.

### Exec Sistem Çağrıları

* `exec()` ailesi sistem çağrıları, mevcut işlemin yürütülecek dosyayı değiştirir.
* Bu çağrılar, yeni bir işlem oluşturmaz. Mevcut işlemin bellek alanını ve kaynaklarını yeni dosya ile değiştirir.
* `exec()` ailesi çağrıları, başarılı olursa, yeni dosyayı yürütür ve geri dönmez. Hata durumunda ise -1 değeri döndürür.

### Wait Sistem Çağrısı

* `wait()` sistem çağrısı, bir işleme ait bir çocuğun sona ermesini bekler.
* `wait()` çağrısı, sona eren çocuğun PID'sini döndürür. Eğer bekleyen çocuk yoksa, `wait()` çağrısı askıda kalır.
* `wait(NULL)` çağrısı, herhangi bir çocuğun sona ermesini bekler.



### Detaylı Açıklama [kod(zombi_execlp_wait.c)](/zombi_execlp_wait.c)

* `fork()` çağrısından sonra, ebeveyn işlem ve çocuk işlem aynı kodu çalıştırmaya devam eder.
* Ebeveyn işlem, `if(pid==0)` koşulunu sağlamaz ve `else` bloğuna girer.
* Ebeveyn işlem, `wait(NULL)` çağrısı ile çocuğun sona ermesini bekler.
* Çocuk işlem, `if(pid==0)` koşulunu sağlar ve `if` bloğuna girer.
* Çocuk işlem, `execlp()` çağrısı ile `/bin/ls` dosyasını yürütür.
* `execlp()` çağrısı başarılı olursa, çocuk işlem sona erer ve geri dönmez.
* Ebeveyn işlem, sona eren çocuğun PID'sini ve son olarak kendi PID'sini yazar.

## Özet

Kod, `fork()` ve `exec()` sistem çağrılarını kullanarak bir çocuk işlem oluşturur ve bu işleme `/bin/ls` dosyasını yürütmesini söyler. Ebeveyn işlem, çocuğun sona ermesini bekler ve ardından sona eren çocuğun PID'sini ve kendi PID'sini yazar.


Kodun Ekran Ciktisi: 
hamza@DESKTOP-FE4MRVU:~/isletim/zombi$ gcc -o zombi2 zombi_execlp_wait.c.c
hamza@DESKTOP-FE4MRVU:~/isletim/zombi$ ./zombi2
1) Fork oncesi
COCUK SUREC 1- pid = 0
zo  zom2  zombi  zombi.c  zombi2  zombi2.c
ANA - pid = 1904
SON - pid = 1904 

*/


#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;

    printf("1) Fork oncesi\n");
    //fork();
    
    pid = fork();

    if(pid==0)
    {
        printf("COCUK SUREC 1- pid = %d\n",pid);
        execlp("/bin/ls","ls",NULL);
        printf("COCUK SUREC 2- pid = %d\n",pid); //EXECE DEN SONRAKI KISIM(COCUKLA ALAKALI KISIM) CALISMAZ
      
    }else{
        wait(NULL);                              //Diger cocuk surec gerceklesmeden bursi calismaz.
        printf("ANA - pid = %d\n",pid);
    }
    
    printf("SON - pid = %d \n",pid);

    return 0;
}