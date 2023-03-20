/*Autor: Igor Tyszer*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    // wyswietlenie na ekran procesow potomnych
    printf("UID:%d, GID:%d, PID:%d, PPID:%d, PGID:%d\n",getuid(),getgid(),getpid(),getppid(),getpgrp());
}
