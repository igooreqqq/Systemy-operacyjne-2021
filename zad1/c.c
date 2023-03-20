/*Igor Tyszer
 * Program wypisujacy identyfikatory UID, GID, PID, PPID i PGID dla
     procesu macierzystego oraz wszystkich procesow potomnych. Procesy
     potomne sa adoptowane przez proces systemd.
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
    for(i=0;i<3;i++) //wykonanie petli 3 razy, w ktorej funkcja fork bedzie tworzyc procesy potomne
    {
        switch (fork()) //funkcja fork tworzy proces potomny, ktory jest kopia procesu macierzystego
        {
            case -1: //obsluga bledu funkcji fork
                perror("fork error");
                exit(EXIT_FAILURE);
            case 0: //zawiera akcje dla procesu potomnego
                sleep(1); //usypia wywolujacy ta funkcje proces potomny na 1 sekunde
                //wyswietlenie na ekran identyfikatorow(wymienionych wyzej) procesow potomnych
                printf("UID:%d, GID:%d, PID:%d, PPID:%d, PGID:%d\n",getuid(),getgid(),getpid(),getppid(),getpgrp());
                break;
            default: //zawiera akcje dla procesu macierzystego
                break;
        }
    } 
    return 0;
}
