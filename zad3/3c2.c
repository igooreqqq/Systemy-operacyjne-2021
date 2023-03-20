/* Igor Tyszer, 15.04.2021
 * Program uruchamiany przez program 3c.c
 * Uruchamia on program 3a.c w procesie potomnym, a takze ustanawia ignorowanie sygnalu
 */

#define _POSIX_C_SOURCE 200112L
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if( argc != 3) //sprawdzenie, czy liczba argumentow jest prawidlowa, a jesli nie jest to wyswietl blad i zakoncz program
    {
        printf("Wpisana liczba argumentow jest nieprawidlowa\n");
        exit(EXIT_FAILURE);
    }
    char *opcja = argv[1];
    int sygnal;
    sygnal = atoi(argv[2]);
    char *arg_sygnal = argv[2];
    printf("Lider: PID procesu to:%d, a PGID to:%d\n",getpid(),getpgrp()); //wyswietlenie procesu, ktory jest liderem grupy
    
    if(signal(sygnal,SIG_IGN) == SIG_ERR) //ustawienie ignorowania sygnalu
    {
        perror("Funkcja signal ma problem z podanym sygnalem");
        exit(EXIT_FAILURE);
    }
    
    int i;
    int PID;
    for(i=0;i<3;i++)
    {
        switch (PID = fork()) //funkcja fork tworzy proces potomny, ktory jest kopia procesu macierzystego
        {
            case -1: //obsluga bledu funkcji fork
                perror("fork error");
                exit(EXIT_FAILURE);
                
            case 0: //zawiera akcje dla procesu potomnego
                execl("./3a.x","3a.x",opcja,arg_sygnal,NULL); //funkcja exec uruchamia trzeci program 3a.c
                perror("execl error"); //obsluga bledow funkcji exec
                _exit(2);
                break;

            default: //zawiera akcje dla procesu macierzystego
                
                break;
        }
    }
    int j;
    int info;
    for(j=0;j<3;j++)
    {
        if((info = wait(NULL))==-1) //proces macierzysty czeka na zakonczenie wyszystkich procesow potomnych
        {
            perror("wait error"); //obsluga bledu funkcji wait
            exit(EXIT_FAILURE);
        }
        printf("Zakonczono proces o PID rownym: %d\n",info); //wyswietlenie statusu zakonczenia procesu potomnego
    }
    return 0;
}
