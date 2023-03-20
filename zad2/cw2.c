/*Autor: Igor Tyszer
 * Zmodyfikowany program z cwiczenia 1 wypisujacy identyfikatory UID,
     GID, PID, PPID i PGID dla procesu macierzystego oraz wszystkich 
     procesow potomnych z ta roznica, ze komunikaty procesow potomnych
     wypisywane sa przez drugi program przez funkcje exec.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    //wyswietlenie na ekran identyfikatorow UID(identyfikator uzytkownika), GID(identyfikator grupy uzytkownika),
    //PID(identyfikator procesu), PPID(identyfikator procesu macierzystego), PGID(identyfikator grupy procesow)
    printf("Proces macierzysty: UID:%d, GID:%d, PID:%d, PPID:%d, PGID:%d\n",getuid(),getgid(),getpid(),getppid(),getpgrp());
    int i;
    for(i=0;i<3;i++) //wykonanie petli 3 razy, w ktorej funkcja fork bedzie tworzyc procesy potomne
    {
        switch (fork()) //funkcja fork tworzy proces potomny, ktory jest kopia procesu macierzystego
        {
            case -1: //obsluga bledu funkcji fork
                perror("fork error");
                exit(EXIT_FAILURE);
                
            case 0: //zawiera akcje dla procesu potomnego
                execl("./exec.x","exec.x",NULL); //funkcja exec uruchamia drugi program, ktory wyswietla procesy potomne
                perror("execl error"); //obsluga bledow funkcji exec
                _exit(2);
                break;

            default: //zawiera akcje dla procesu macierzystego
                //zawieszenie dzialania procesu macierzystego do momentu zakonczenia sie procesow potomych
                if(wait(NULL)==-1)
                {
                    perror("wait error"); //obsluga bledu funkcji wait
                    exit(EXIT_FAILURE);
                }
                break;
        }
    }
    return 0;
}
