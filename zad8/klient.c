/* Igor Tyszer,  Krakow 23.05.21
 * Program klienta
 */

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
mqd_t otwieranie;

void koniec(void) //funkcja ktora wykona sie przy exit()
{
    int PID;
    PID = getpid();
    char nazwa[6];
    sprintf(nazwa, "/%d", PID);
    zamknijKolejke(otwieranie); //zamknij kolejke serwera
    zamknijKolejke(odbieranie); //zamknij kolejke klienta
    usunKolejke(nazwa); //usun kolejke klienta
    printf("\nPomyslnie zamknieto i usunieto kolejke!\n");
}


void sighandler() //definicja funkcji do wlasnej obslugi sygnalu
{
    int PID;
    PID = getpid();
    char nazwa[6];
    sprintf(nazwa, "/%d", PID);
    zamknijKolejke(otwieranie); //zamknij kolejke serwera
    zamknijKolejke(odbieranie); //zamknij kolejke klienta
    usunKolejke(nazwa); //usun kolejke klienta

    printf("\nUsunieto kolejke po awaryjnym przerwaniu programu kombinacja CTRL-C!\n");
    _exit(0);
}

int main(int argc, char *argv[])
{
    if(atexit(koniec) == -1) //rejestracja funkcji koniec() do wywolania przez exit()
    {
        perror("atexit error"); //obsluga bledow funkcji atexit
        _exit(EXIT_FAILURE);
    }
    
    struct mq_attr attr;
    
    //reczne ustawienie atrybutow kolejki
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = 30;
    attr.mq_curmsgs = 0;
    
    int PID;
    PID = getpid(); //pobranie PID procesu klienta
    char nazwa[6];
    sprintf(nazwa, "/%d", PID);
    
    stworzKolejke(nazwa, O_RDONLY | O_CREAT | O_EXCL, 0644, &attr); //stworzenie kolejki klienta
    odbieranie = otworzKolejke(nazwa, O_RDONLY); //otworzenie kolejki klienta
    printf("Utworzono kolejke o nazwie %s i deskryptorze: %d\n", nazwa, odbieranie); //wyswietlenie na ekran nazwy i deskryptoru kolejki klienta
    
    if(signal(SIGINT,sighandler) == SIG_ERR) //wlasna obsluga sygnalu
    {
        perror("Funkcja signal ma problem z podanym sygnalem");
        _exit(EXIT_FAILURE);
    }
    
    //wyswietlenie na ekran ustawien atrybutow kolejki klienta
    printf("mq_flags: %ld\n", attr.mq_flags);
    printf("mq_maxmsg: %ld\n", attr.mq_maxmsg);
    printf("mq_msgsize: %ld\n", attr.mq_msgsize);
    printf("mq_curmsgs: %ld\n", attr.mq_curmsgs);
    
    otwieranie = otworzKolejke(mqname, O_WRONLY); //otworz kolejke serwera
    
    char dzialanie[20];
    
    printf("Prosze wpisac dzialanie typu: liczba znak liczba\n\n");
    
    while( fgets(dzialanie, 20, stdin) != 0); //petla ktora oczekuje na wpisanie dzialania, mozna przerwac kombinacja CTRL-D
    
    wyslijKomunikat(otwieranie,nazwa,sizeof(nazwa),2); //wyslij nazwe PID klienta do serwera
    
    wyslijKomunikat(otwieranie,dzialanie,sizeof(dzialanie),1); //wyslij dzialanie do serwera
        
    printf("Dzialanie wynosi: %s\n",dzialanie);
    
    sleep(5);
    char wynik[60];
    
    odbierzKomunikat(odbieranie, wynik, 60, NULL); //odbierz od serwera wynik
    
    printf("Wynik dzialania to: %s\n", wynik); //wyswietl wynik dzialania odebrany od serwera na ekran
    
    exit(0);
}
