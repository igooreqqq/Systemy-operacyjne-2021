/*Igor Tyszer
 * Program wypisujacy identyfikatory UID, GID, PID, PPID i PGID dla
     danego procesu.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    //wyswietlenie na ekran identyfikatorow UID(identyfikator uzytkownika), GID(identyfikator grupy uzytkownika),
    //PID(identyfikator procesu), PPID(identyfikator procesu macierzystego), PGID(identyfikator grupy procesow)
    printf("UID:%d, GID:%d, PID:%d, PPID:%d, PGID:%d\n",getuid(),getgid(),getpid(),getppid(),getpgrp());
    return 0;
}
