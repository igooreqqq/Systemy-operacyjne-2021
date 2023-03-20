/*Igor Tyszer
 * Program wypisujacy identyfikatory UID, GID, PID, PPID i PGID dla
     procesu macierzystego oraz wszystkich procesow potomnych.
     Procesy pojawiaja sie na ekranie grupowane pokoleniami od 
     najstarszego do najmlodszego. Proces macierzysty konczy sie
     dopiero po procesach potomnych.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    //wyswietlenie na ekran identyfikatorow UID(identyfikator uzytkownika), GID(identyfikator grupy uzytkownika),
    //PID(identyfikator procesu), PPID(identyfikator procesu macierzystego), PGID(identyfikator grupy procesow)
    printf("Proces macierzysty: UID:%d, GID:%d, PID:%d, PPID:%d, PGID:%d\n",getuid(),getgid(),getpid(),getppid(),getpgrp());
    int i;
    for(i=1;i<4;i++) //wykonanie petli 3 razy, w ktorej funkcja fork bedzie tworzyc procesy potomne
    {
        switch (fork()) //funkcja fork tworzy proces potomny, ktory jest kopia procesu macierzystego
        {
            case -1: //obsluga bledu funkcji fork
                perror("fork error");
                exit(EXIT_FAILURE);
            case 0: //zawiera akcje dla procesu potomnego
                //wyswietlenie na ekran identyfikatorow(wymienionych wyzej) procesow potomnych
                printf("%d.UID:%d, GID:%d, PID:%d, PPID:%d, PGID:%d\n",i,getuid(),getgid(),getpid(),getppid(),getpgrp());
                sleep(2); //procesy potomne wyswietlaja pokoleniami w grupach co 2 sekundy
            default: //zawiera akcje dla procesu macierzystego
                break;
        }
    }
    sleep(6);//proces macierzysty kończy się po 6 sekundach od rozpoczecia programu(czyli gdy wykonaja sie wszystkie procesy potomne)
            
    return 0;
}

