/*Igor Tyszer
 * Program wypisujacy identyfikatory UID, GID, PID, PPID i PGID dla
     procesu macierzystego oraz wszystkich procesow potomnych.
     Kazdy proces potomny jest liderem swojej wlasnej grupy procesow,
     czyli PGID tego procesu jest rowne jego PID.
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
                setpgid(0, 0); //zmienienie identyfikatoru PGID bieżącego procesu na taki ktory jest równy jego PID
                //wyswietlenie na ekran identyfikatorow(wymienionych wyzej) procesow potomnych
                printf("UID:%d, GID:%d, PID:%d, PPID:%d, PGID:%d\n",getuid(),getgid(),getpid(),getppid(),getpgrp());
                break;
            default: //zawiera akcje dla procesu macierzystego
                //zawieszenie dzialania procesu macierzystego do momentu zakonczenia wszystkich procesow potomych
                wait(); 
                break;
        }
    } 
    return 0;
}
