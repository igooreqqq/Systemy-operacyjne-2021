/* Igor Tyszer, 15.04.2021
 * Program ustawia obsluge sygnalu na 3 sposoby zgodnie z opcja podana
     jako argument wywolania programu, a nastepnie czeka na sygnal.
     Numer sygnalu jest rowniez przekazywany jako argument wywolania 
     programu. Proces wypisuje na ekranie swój PID, a także swój PGID.
     */

#define _POSIX_C_SOURCE 200112L
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>

void sighandler(int sygnal) //definicja funkcji do wlasnej obslugi sygnalu
{
    extern const char * const sys_siglist[];
    printf("Numer sygnalu: %d, a jego nazwa to:%s\n",sygnal,sys_siglist[sygnal]); //funkcja wypisuje nr sygnalu, a takze jego nazwe
}

int main(int argc, char *argv[])
{
    if( argc != 3) //sprawdzenie, czy liczba argumentow jest prawidlowa, a jesli nie jest to wyswietl blad i zakoncz program
    {
        printf("Wpisana liczba argumentow jest nieprawidlowa\n");
        exit(EXIT_FAILURE);
    }
    printf("PID procesu to:%d, a PGID to:%d\n",getpid(),getpgrp()); //wyswietlenie na ekran PID procesu, a takze jego PGID
    
    char *opcja = argv[1];
    int sygnal;
    sygnal = atoi(argv[2]);
    
    
    if(strcmp(opcja,"default") == 0) //porownanie, czy wprowadzona opcja to default
    {
        if(signal(sygnal,SIG_DFL) == SIG_ERR) //wykonanie operacji domyslnej
        {
            perror("Funkcja signal ma problem z podanym sygnalem");
            exit(EXIT_FAILURE);
        }
    }
    
    else if(strcmp(opcja,"ignore") == 0) //porownanie, czy wprowadzona opcja to ignore
    {
        if(signal(sygnal,SIG_IGN) == SIG_ERR) //ignorowanie sygnalu
        {
            perror("Funkcja signal ma problem z podanym sygnalem");
            exit(EXIT_FAILURE);
        }
    }
    
    else if(strcmp(opcja,"intercept") == 0) //porownanie, czy wprowadzona opcja to intercept
    {
        if(signal(sygnal,sighandler) == SIG_ERR) //wlasna obsluga sygnalu
        {
            perror("Funkcja signal ma problem z podanym sygnalem");
            exit(EXIT_FAILURE);
        }
    }
    
    else //jesli wprowadzona opcja jest inna od powyzszych, zakoncz program i poinformuj uzytkownika o bledzie
    {
        printf("Wprowadzono zly rozkaz!\n");
        exit(EXIT_FAILURE);
    }
    pause(); //program oczekuje na sygnal
    
    return 0;
}
