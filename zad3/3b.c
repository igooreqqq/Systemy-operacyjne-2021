/* Igor Tyszer, 15.04.2021
 * Program, ktory w procesie potomnym uruchamia program 3a.c,
     po czym z procesu macierzystego wysyla do niego sygnal.
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
    if( argc != 4) //sprawdzenie, czy liczba argumentow jest prawidlowa, a jesli nie jest to wyswietl blad i zakoncz program
    {
        printf("Wpisana liczba argumentow jest nieprawidlowa\n");
        exit(EXIT_FAILURE);
    }
    char *opcja = argv[2];
    int sygnal;
    sygnal = atoi(argv[3]);
    char *arg_sygnal = argv[3];
    int PID;
    switch (PID = fork()) //funkcja fork tworzy proces potomny, ktory jest kopia procesu macierzystego
        {
            case -1: //obsluga bledu funkcji fork
                perror("fork error");
                exit(EXIT_FAILURE);
                
            case 0: //zawiera akcje dla procesu potomnego
                execl("./3a.x","3a.x",opcja,arg_sygnal,NULL); //funkcja exec uruchamia drugi program 3a.c
                perror("execl error"); //obsluga bledow funkcji exec
                _exit(2);
                break;

            default: //zawiera akcje dla procesu macierzystego
                sleep(2); //uspienie procesu na 2 sekundy
                if((kill(PID,0)) == -1) //sprawdzenie czy podany proces istnieje
                {
                    perror("Proces o podanym PID nie istieje.\n");
                    exit(EXIT_FAILURE);
                }
                else
                {
                    kill(PID,sygnal); //jesli proces istnieje, to wyslij do niego sygnal
                    printf("Wyslano sygnal %d\n",sygnal); //poinformowanie o wyslaniu sygnalu
                }
                break;
        }
        return 0;
}
