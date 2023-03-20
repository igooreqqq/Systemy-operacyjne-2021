/* Igor Tyszer,  Krakow 23.05.21
 * W programie przy pomocy mechanizmu kolejek komunikatow zostalo 
     zrealizowane zadanie 8 klient-serwer. Program tworzy serwer,
     ktory oczekuje na wprowadzenie dzialania arytmetycznego w programie
     klienta, ktore to jest przesylane do serwera, serwer oblicza
     to dzialanie, a wynik zostaje odeslany do programu klienta, ktory
     wyswietla wynik. Program serwera moze obsluguwac wiele programow 
     klienta na raz. */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <signal.h>
#include <mqueue.h>

#include "funkcje.h"
#include "nazwa.h"

mqd_t odbieranie;

void koniec(void) //funkcja po wywolaniu exit()
{
    zamknijKolejke(odbieranie); //zamyka kolejke serwera
    usunKolejke(mqname); //usuwa kolejke serwera
    printf("\nUsunieto kolejke po awaryjnym przerwaniu programu kombinacja CTRL-C!\n");
}

void sighandler() //definicja funkcji do wlasnej obslugi sygnalu
{
    exit(0);
}

int main()
{
    if(atexit(koniec) == -1) //rejestracja funkcji koniec() do wywolania przez exit()
    {
        perror("atexit error"); //obsluga bledow funkcji atexit
        _exit(EXIT_FAILURE);
    }
    
    struct mq_attr attr;
    
    //reczne ustawianie atrybytow kolejki
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = 30;
    attr.mq_curmsgs = 0;
    
    
    stworzKolejke(mqname, O_RDONLY | O_CREAT | O_EXCL, 0644, &attr); //stworzenie kolejki serwera
    odbieranie = otworzKolejke(mqname, O_RDONLY); //otworzenie kolejki serwera
        
    
    printf("Utworzono kolejke serwera o nazwie %s i deskryptorze: %d\n", mqname, odbieranie);
    
    if(signal(SIGINT,sighandler) == SIG_ERR) //wlasna obsluga sygnalu
    {
        perror("Funkcja signal ma problem z podanym sygnalem");
        exit(EXIT_FAILURE);
    }
    
    //wyswietlenie ustawien atrybutow na ekran
    printf("mq_flags: %ld\n", attr.mq_flags);
    printf("mq_maxmsg: %ld\n", attr.mq_maxmsg);
    printf("mq_msgsize: %ld\n", attr.mq_msgsize);
    printf("mq_curmsgs: %ld\n", attr.mq_curmsgs);
    
    char nazwa[60]; //tablica znakow dla nazwy PID
    char dzialanie[60]; //tablica znakow dla dzialania
        
    
    while(1)
    {
        if(odbierzKomunikat(odbieranie, nazwa, 60, NULL) == -1) //odbieranie od klienta nazwy PID
        {
        perror(" mq_receive error");
        exit(EXIT_FAILURE);
        }
        else{
        int PID;
        char f[1];
        sscanf(nazwa, "%c%d", f, &PID);
        printf("\nPID wynosi: %d\n", PID); //wyswietl na ekran PID klienta
        }
        
        if(odbierzKomunikat(odbieranie, dzialanie, 60, NULL) == -1) //odbieranie od klienta dzialania
        {
            perror(" mq_receive error");
            exit(EXIT_FAILURE);
        }
        else{
        printf("Dzialanie: %s\n",dzialanie); //wyswietlenie na ekran dzialanie
        
        int a;
        int b;
        char c[1];
        int wynik;
        
        sscanf(dzialanie, "%d %s %d", &a, c, &b);
        printf("%d %s %d\n",a,c,b);
        
        if(strcmp(c,"+") == 0) //porownanie, czy znak to dodawanie
        {
            wynik = a + b;
            printf("Wynik po dzialaniu wynosi: %d\n", wynik);
        }
        if(strcmp(c,"-") == 0) //porownanie, czy znak to odejmowanie
        {
            wynik = a - b;
            printf("Wynik po dzialaniu wynosi: %d\n", wynik);
        }
        if(strcmp(c,"*") == 0) //porownanie, czy znak to mnozenie
        {
            wynik = a * b;
            printf("Wynik po dzialaniu wynosi: %d\n", wynik);
        }
        if(strcmp(c,"/") == 0) //porownanie, czy znak to dzielenie
        {
            wynik = a / b;
            printf("Wynik po dzialaniu wynosi: %d\n", wynik);
        }
        
        char wynikchar[20];
        sprintf(wynikchar, "%d", wynik);
        
        sleep(6);
        
        mqd_t otwieranie;
        
        otwieranie = otworzKolejke(nazwa, O_WRONLY); //otworz kolejke klienta
        
        wyslijKomunikat(otwieranie,wynikchar,sizeof(wynikchar),1); //wyslij do klienta wynik dzialania
        
        zamknijKolejke(otwieranie); //zamknij kolejke klienta
        }
    }
    return 0;
}
