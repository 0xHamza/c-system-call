# c-system-call
C system call example codes: fork, double fork, exec, wait, shared memory, zombi process


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

### Double Fork [kod(soru2_doublefork.c)](/soru2_doublefork.c):

```C
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
```

Kod, arka arkaya pid_f1 ve pid_f2 olmak üzere iki çatal oluşturur. Bu, programın toplam dört süreç oluşturacağı anlamına gelir: orijinal ana süreç ve üç çocuk süreç.

İşte olanlar:

İlk fork() bir çocuk süreç oluşturur ve pid_f1 çocuk süreçte 0'a ve ana süreçte çocuk sürecin süreç kimliğine ayarlanır.
İkinci fork(), 1. adımda oluşturulan hem ana hem de alt süreçlerden başka bir alt süreç oluşturur. Bu, şu anda dört süreç olduğu anlamına gelir: orijinal ana süreç, ilk çocuk süreç ve ikinci fork() tarafından oluşturulan iki yeni çocuk süreç.
Şimdi çıktıyı analiz edelim:

ANA pid_f1:8214 ve ANA pid_f1:8211 iki ana süreç (orijinal ana süreç ve ilk çocuk süreç) tarafından yazdırılır. Üst süreçteki wait(NULL) çağrısı, üst sürecin mesajı yazdırmadan önce alt sürecin bitirmesini beklemesini sağlar.
COCUK pid_f1:8212 ve COCUK pid_f1:8213, ikinci fork() tarafından oluşturulan iki çocuk süreç tarafından yazdırılır.
SON mesajı dört süreç tarafından da yazdırılır, bu yüzden çıktıda dört kez görünür.

Yazdırılan süreç kimlikleri, mesajları yazdıran süreçlerin kimlikleridir. Süreçler eşzamanlı olarak çalıştığı için çıktıların sırası garanti edilmez.
```Bash
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
```

### Forked Variables [kod(soru_forkedvariables.c)](/soru_forkedvariables.c):

```C
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

```
Çıktının nedeni fork() işlevinin çalışma şeklinden kaynaklanmaktadır. fork() çağrıldığında, mevcut süreci (ana süreç) çoğaltarak yeni bir süreç (alt süreç) oluşturur. Çocuk süreç, değişkenlerin değerleri de dahil olmak üzere ebeveynin bellek alanının bir kopyasını alır.

Bu kodda fork(), a 20 olarak başlatıldıktan sonra çağrılır. Alt süreç, a'nın 20 değerine sahip bir kopyasını alır. Daha sonra, alt süreçte a değeri 10 azaltılır, böylece a değeri 10 olur. Üst süreçte, a 10 artırılır, böylece a 30 olur.

Çıktı, hem üst hem de alt süreçlerdeki a değerlerini gösterir. Ana ve alt süreçler eşzamanlı olarak çalıştığı için çıktının sırası garanti edilmez.

Ekran Ciktisi:
```Bash
hamza@DESKTOP-FE4MRVU:~/isletim/fork$ gcc -o soru soru_forkedvariables.c
hamza@DESKTOP-FE4MRVU:~/isletim/fork$ ./soru
a'nin baslangic degeri: 20 
p = 30 ana surec
c = 10 cocuk surec
```

### Kaç Adet Fork Çalışır [kod(fokrkkac.c)](/forkkac.c):

Soru: Fork çalışınca kaç kere çalışır: her bir satır 2^n, 2^forkSayisi kadar calisir

```C
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
```
Ekran Ciktisi:
```Bash
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
```

#### Deneme [kod(deneme.c)](/deneme.c)

```C
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
```

### Fork Zombi Exec Detaylı Açıklama [kod(zombi_execlp_wait.c)](/zombi_execlp_wait.c)

* `fork()` çağrısından sonra, ebeveyn işlem ve çocuk işlem aynı kodu çalıştırmaya devam eder.
* Ebeveyn işlem, `if(pid==0)` koşulunu sağlamaz ve `else` bloğuna girer.
* Ebeveyn işlem, `wait(NULL)` çağrısı ile çocuğun sona ermesini bekler.
* Çocuk işlem, `if(pid==0)` koşulunu sağlar ve `if` bloğuna girer.
* Çocuk işlem, `execlp()` çağrısı ile `/bin/ls` dosyasını yürütür.
* `execlp()` çağrısı başarılı olursa, çocuk işlem sona erer ve geri dönmez.
* Ebeveyn işlem, sona eren çocuğun PID'sini ve son olarak kendi PID'sini yazar.

### Özet

Kod, `fork()` ve `exec()` sistem çağrılarını kullanarak bir çocuk işlem oluşturur ve bu işleme `/bin/ls` dosyasını yürütmesini söyler. Ebeveyn işlem, çocuğun sona ermesini bekler ve ardından sona eren çocuğun PID'sini ve kendi PID'sini yazar.


## Shared Memory W/R
