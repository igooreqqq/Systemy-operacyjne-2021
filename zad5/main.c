/* Igor Tyszer,   Krakow 27.04.2021 
 W programie przy pomocy potokow nazwanych zaimplementowano problem
     "Producenta i konsumenta". Producent pobiera porcjami dane z 
     wejsciowego pliku tekstowego i wstawia go jako towar do potoku, 
     a konsument rowniez porcjami pobiera te dane z potoku i wstawia je 
     do pliku wyjsciowego. Po zakonczeniu programu oba pliki tekstowe 
     powinny byc takie same, sprawdza to polecenie diff -s wywolywane 
     od razu po zakonczeniu sie programu. Program sklada sie z programu
     glownego, ktory uruchamia w procesach potomnych program producent.c
     oraz konsument.c, czeka na ich zakonczenie a po ich zakonczeniu 
     usuwa potok.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>

void koniec(void)
{
    unlink("fifopipe"); //usuniecie pliku ktory utworzyl potok FIFO
}

int main(int argc, char *argv[])
{
    if(argc != 6) //sprawdzenie, czy liczba argumentow jest prawidlowa, a jesli nie jest to wyswietl blad i zakoncz program
    {
        printf("Wpisana liczba argumentow jest nieprawidlowa\n");
        exit(EXIT_FAILURE);
    }
    
    if(atexit(koniec) == -1) //rejestracja funkcji koniec() do wywolania przez exit()
    {
        perror("atexit error"); //obsluga bledow funkcji atexit
        exit(EXIT_FAILURE);
    }
    
    if(mkfifo(argv[3],0777) == -1) //utworzenie potoku fifo
    {
        perror("mkfifo error"); //obsluga bledow funkcji mkfifo
        exit(EXIT_FAILURE);
    }
    
    switch (fork()) //funkcja fork tworzy proces potomny, ktory jest kopia procesu macierzystego
    {
        case -1: //obsluga bledu funkcji fork
            perror("fork error");
            exit(EXIT_FAILURE);
        case 0: //zawiera akcje dla procesu potomnego
            execl("./producent.x",argv[1],argv[3],argv[4],NULL);
            perror("execl error"); //obsluga bledow funkcji exec
            _exit(2);
            break;
        default: //zawiera akcje dla procesu macierzystego
            
            break;
    }
    
    switch (fork()) //funkcja fork tworzy proces potomny, ktory jest kopia procesu macierzystego
    {
        case -1: //obsluga bledu funkcji fork
            perror("fork error");
            exit(EXIT_FAILURE);
        case 0: //zawiera akcje dla procesu potomnego
            execl("./konsument.x",argv[2],argv[3],argv[5],NULL);
            perror("execl error"); //obsluga bledow funkcji exec
            _exit(2);
            break;
        default: //zawiera akcje dla procesu macierzystego
            
            break;
    }

    if(wait(NULL) == -1) //czekaj na zakonczenie sie pierwszego procesu potomnego
    {
        perror("wait error"); //obsluga bledow funkcji wait
        exit(EXIT_FAILURE);
    }
    if(wait(NULL) == -1) //czekaj na zakonczenie sie drugiego procesu potomnego
    {
        perror("wait error"); //obsluga bledow funkcji wait
        exit(EXIT_FAILURE);
    }
    
    exit(0); //zakonczenie programu a po nim usuniecie pliku utworzonego podczas tworzenia potoku FIFO
    
    return 0;
}
