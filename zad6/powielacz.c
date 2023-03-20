/* Igor Tyszer,    Krakow 11.05.21
 * W programie przy pomocy semaforow nazwanych standardu POSIX
     zaimplementowano zadanie wzajemnego wykluczania dla procesow.
     Program powielacz.c na poczatku tworzy plik tekstowy, umieszcza
     w nim "0", a program wykluczanie.c w swojej sekcji krytycznej
     odczytuje liczbe z pliku, powieksza ja o jeden a nastepnie znowu
     zapisuje ja do pliku tekstowego. Program powielacz.c w swoim 
     procesie potomnym wykonuje program wykluczanie.c.
     Liczbe procesow oraz ilosc sekcji krytycznych nalezy podac przez
     argumenty programu "powielacza". */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <string.h>
#include <signal.h>
#include "biblioteka.h"

#define nazwaSemafora "/Semafor"

void koniec(void)
{
    usuniecieSemafora(nazwaSemafora); //funkcja usuwajaca utworzony semafor
}


void sighandler() //definicja funkcji do wlasnej obslugi sygnalu
{
    usuniecieSemafora(nazwaSemafora); //funkcja usuwajaca utworzony semafor

    printf("\nUsunieto semafor po awaryjnym przerwaniu programu kombinacja CTRL-C!\n");
}

int zwroconeBajty;

int main(int argc, char *argv[])
{
    if(argc != 5) //sprawdzenie, czy liczba argumentow jest prawidlowa, a jesli nie jest to wyswietl blad i zakoncz program
    {
        printf("Wpisana liczba argumentow jest nieprawidlowa, w argumentach nalezy umiescic: powielacz.x wykluczanie.x <plik tekstowty> <ilosc procesow> <ilosc SK>\n");
        exit(EXIT_FAILURE);
    }
    
    if(atexit(koniec) == -1) //rejestracja funkcji koniec() do wywolania przez exit()
    {
        perror("atexit error"); //obsluga bledow funkcji atexit
        exit(EXIT_FAILURE);
    }
    
    sem_t *sem;
    void *p = &sem;
    
    sem = nowySemafor(nazwaSemafora,O_CREAT | O_EXCL,0644,1);
    
    int val;
    
    if(signal(SIGINT,sighandler) == SIG_ERR) //wlasna obsluga sygnalu
    {
        perror("Funkcja signal ma problem z podanym sygnalem");
        exit(EXIT_FAILURE);
    }
    
    wartoscSemafora(sem, &val); //funkcja sprawdzajaca aktualna wartosc semafora
    
    printf("Utworzono semafor o adresie: %p, a jego wartosc to: %d\n",p,val);
    
    int wejscie;
    char str[1];
    
    if((wejscie = open(argv[2],O_WRONLY | O_CREAT,0644)) == -1) //otworzenie pliku wejsciowego i zwrocenie jego deskryptoru
    {
        perror("open error"); //obsluga bledow funkcji open
        exit(EXIT_FAILURE);
    }
    
    if(write(wejscie,"0",1) == -1) //zapisanie do potoku danych odczytanych z deskryptora wejscia
    {
        perror("write error"); //obsluga bledow funkcji write
        exit(EXIT_FAILURE);
    }
    
    if(close(wejscie) == -1) //zamkniecie deskryptora wejscia
    {
        perror("close error"); //obsluga bledow funkcji close
        exit(EXIT_FAILURE); 
    }
    
    int liczbaProcesow;
    int iloscSekcji;
    liczbaProcesow = atoi(argv[3]);
    iloscSekcji = atoi(argv[4]);
    
    for(int i = 0; i < liczbaProcesow; i++)
    {
        switch(fork()) //funkcja tworzoca procesy potomne
        {
            case -1: //obsluga bledu funkcji fork
                perror("fork error");
                exit(EXIT_FAILURE);
            
            case 0:  
                execl("./wykluczanie.x",argv[1],argv[2],argv[4]);
                perror("execl error"); //obsluga bledow funkcji exec
                _exit(2);
                
                break;
                
            default:
                
                break;
            
        }
    }
    
    for(int i = 0; i < liczbaProcesow; i++)
    {
        if(wait(NULL) == -1) //poczekaj na zakonczenie wszystkich procesow potomnych
        {
            perror("wait error"); //obsluga bledow funkcji wait
            exit(EXIT_FAILURE); 
        }
    }
    
    zamykanieSemafora(sem); //funkcja zamykajaca otwarty semafor
    
    if((wejscie = open(argv[2],O_RDONLY)) == -1) //otworzenie pliku wejsciowego i zwrocenie jego deskryptoru
    {
        perror("open error"); //obsluga bledow funkcji open
        exit(EXIT_FAILURE);
    }
    
    zwroconeBajty = read(wejscie, &str, 1);
    
    int numer;
    numer = atoi(str);
                        
    printf("\nNa koniec numer wynosi: %d\n",numer);
    
    if(numer == iloscSekcji*liczbaProcesow)
    {
        printf("Co zgadza sie z oczekiwanym wynikiem.\n");
    }
    else
    {
        printf("Co nie zgadza sie z oczekiwanym wynikiem\n");
    }
    
    if(close(wejscie) == -1) //zamkniecie deskryptora wejscia
    {
        perror("close error"); //obsluga bledow funkcji close
        exit(EXIT_FAILURE); 
    }
    
    exit(0);
    
    return 0;
}
