/* Igor Tyszer, 15.04.2021
 * Program, ktory tworzy proces potomny i uruchamia w nim program 3c2.c,
     ktory ustawia ignorowanie sygnalu, staje sie liderem swojej grupy
     procesow, a nastepnie tworzy kilka procesow potomnych, ktore
     uruchamiaja program 3a.c. Pierwszy proces macierzysty po krotkim
     czasie uspienia wysyla sygnal do calej grupy procesow.
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
    if( argc != 5) //sprawdzenie, czy liczba argumentow jest prawidlowa, a jesli nie jest to wyswietl blad i zakoncz program
    {
        printf("Wpisana liczba argumentow jest nieprawidlowa\n");
        exit(EXIT_FAILURE);
    }
    char *opcja = argv[3];
    int sygnal;
    sygnal = atoi(argv[4]);
    char *arg_sygnal = argv[4];
    
    
    int PID;
    int PID_grupy;
    
    switch (PID = fork()) //funkcja fork tworzy proces potomny, ktory jest kopia procesu macierzystego
        {
            case -1: //obsluga bledu funkcji fork
                perror("fork error");
                exit(EXIT_FAILURE);
                
            case 0: //zawiera akcje dla procesu potomnego
                if(setpgid(0, 0)==-1) //zmienienie identyfikatoru PGID bieżącego procesu na taki ktory jest równy jego PID
                {
                    perror("setpgid error"); //obsluga bledu funkcji setpgid
                    exit(EXIT_FAILURE);
                }
                execl("./3c2.x","3c2.x",opcja,arg_sygnal,NULL); //funkcja exec uruchamia drugi program 3c2.c
                perror("execl error"); //obsluga bledow funkcji exec
                _exit(2);
                break;

            default: //zawiera akcje dla procesu macierzystego
                sleep(2); //uspienie procesu na 2 sekundy
                PID_grupy = getpgid(PID);
                if((kill(PID_grupy,0)) == -1) //sprawdzenie czy proces o podanym PID istnieje
                {
                    perror("Proces o podanym PID nie istieje.\n");
                    exit(EXIT_FAILURE);
                }
                else
                {
                    printf("Wyslano sygnal %d\n",sygnal); // informowanie uzytkownika o wysylaniu sygnalu
                    kill(-1 * PID_grupy,sygnal); //wyslanie sygnalu do calej grupy procesow
                    
                }
                break;
        }
        return 0;
}
