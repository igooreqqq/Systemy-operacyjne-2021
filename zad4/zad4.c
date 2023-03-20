/* Igor Tyszer, 21.04.2021
 * W programie przy pomocy potokow nienazwanych zaimplementowano problem
     "Producenta i konsumenta". Producent pobiera porcjami dane z 
     wejsciowego pliku tekstowego i wstawia go jako towar do potoku, 
     a konsument rowniez porcjami pobiera te dane z potoku i wstawia je 
     do pliku wyjsciowego. Po zakonczeniu programu oba pliki tekstowe 
     powinny byc takie same, sprawdza to polecenie diff -s wywolywane 
     od razu po zakonczeniu sie programu.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>

int main(int argc, char *argv[])
{
    if( argc != 3) //sprawdzenie, czy liczba argumentow jest prawidlowa, a jesli nie jest to wyswietl blad i zakoncz program
    {
        printf("Wpisana liczba argumentow jest nieprawidlowa\n");
        exit(EXIT_FAILURE);
    }
    
    int fd[2];
    if(pipe(fd) == -1) // funckcja tworzaca potok
    {
        perror("pipe error"); // obsluga bledow funkcji pipe
        exit(EXIT_FAILURE);
    }
    int str[5];
    int wejscie;
    int wyjscie;
    int zwroconeBajty;
    srand(time(NULL));
    
    switch(fork()) //funkcja fork tworzy proces potomny, ktory jest kopia procesu macierzystego
    {
        case -1:
                perror("fork error"); //obsluga bledu funkcji fork
                exit(EXIT_FAILURE);
                
        case 0:
                if(close(fd[1]) == -1) //zamkniecie deskryptoru zapisu, poniewaz w tym procesie nie zapisujemy nic do potoku
                {
                    perror("close error"); //obsluga bledow funkcji close
                    exit(EXIT_FAILURE);
                }
                
                if((wyjscie = open(argv[2],O_WRONLY)) == -1) //otworzenie pliku wyjsciowego i zwrocenie jego deskryptoru
                {
                    perror("open error"); //obsluga bledow funkcji open
                    exit(EXIT_FAILURE);
                }
                
                while((zwroconeBajty = read(fd[0], &str, 4))>0) //wykonuj dopóki czytanie str z potoku, porcja konsumenta to 2
                {
                    int randomTime = 2 + rand() % (5);
                    sleep(randomTime); //uspij proces na losowy czas z zakresie od 2 do 6 sekund
                    
                    if(zwroconeBajty == -1) //jesli nie udalo sie odczytac, wyswietl blad
                    {
                        perror("read error"); //obsluga bledow funkcji read
                        exit(EXIT_FAILURE);
                    }
                    
                    else
                    {
                        if(write(wyjscie, &str, zwroconeBajty) == -1) //zapisz dane pobrane z potoku do pliku o deskryptorze wyjscie
                        {
                            perror("write error"); //obsluga bledow funkcji write
                            exit(EXIT_FAILURE);
                        }
                        if(write(STDOUT_FILENO,"Konsument pobiera: ",19) == -1) //wypisz na ekranie tekst
                        {
                            perror("write error"); //obsluga bledow funkcji write
                            exit(EXIT_FAILURE);
                        }
                        if(write(STDOUT_FILENO, str, zwroconeBajty) == -1) //wypisz na ekranie to, co zostalo pobrane z potoku
                        {
                            perror("write error"); //obsluga bledow funkcji write
                            exit(EXIT_FAILURE);
                        }
                        printf("\n");
                    }
                }
                if(close(fd[0]) == -1) //zamknij deskryptor odczytu z potoku
                {
                    perror("close error"); //obsluga bledow funkcji close
                    exit(EXIT_FAILURE);
                }
                if(close(wyjscie) == -1) //zamknij deskryptor pliku wyjsciowego
                {
                    perror("close error"); //obsluga bledow funkcji close
                    exit(EXIT_FAILURE);
                }
                break;
            
        default:
                if(close(fd[0]) == -1) //zamknij deskryptor odczytu z potoku, poniewaz w tym procesie tylko zapisujemy do potoku
                {
                    perror("close error"); //obsluga bledow funkcji close
                    exit(EXIT_FAILURE);
                }
                
                if((wejscie = open(argv[1],O_RDONLY)) == -1) //otworzenie pliku wejsciowego i zwrocenie jego deskryptoru
                {
                    perror("open error"); //obsluga bledow funkcji open
                    exit(EXIT_FAILURE);
                }
                
                while((zwroconeBajty = read(wejscie, &str, 5))>0) //wykonuj dopóki czytanie str z deskryptora wejscia, porcja producenta to 4
                {
                    int randomTime = 2 + rand() % (5);
                    sleep(randomTime); //uspij proces na losowy czas w zakresie od 2 do 6 sekund
                    
                    if(zwroconeBajty == -1) //jesli nie udalo sie odczytac wyswietl blad
                    {
                        perror("read error"); //obsluga bledow funkcji read
                        exit(EXIT_FAILURE);
                    }
                    
                    else
                    {
                        if(write(fd[1],&str,zwroconeBajty) == -1) //zapisanie do potoku danych odczytanych z deskryptora wejscia
                        {
                            perror("write error"); //obsluga bledow funkcji write
                            exit(EXIT_FAILURE);
                        }
                        if(write(STDOUT_FILENO,"Producent wypisuje: ",20) == -1) //wypisz na ekranie tekst
                        {
                            perror("write error"); //obsluga bledow funkcji write
                            exit(EXIT_FAILURE);
                        }
                        if(write(STDOUT_FILENO, str, zwroconeBajty) == -1) //wypisz na ekranie to co zostalo odczytane z deskryptora wejscia
                        {
                            perror("write error"); //obsluga bledow funkcji write
                            exit(EXIT_FAILURE);
                        }
                        printf("\n");
                    }
                }
                if(close(fd[1]) == -1) //zamknij deskryptor zapisu do potoku
                {
                    perror("close error"); //obsluga bledow funkcji close
                    exit(EXIT_FAILURE);
                }
                if(close(wejscie) == -1) //zamknij deskryptor pliku wejsciowego
                {
                    perror("close error"); //obsluga bledow funkcji close
                    exit(EXIT_FAILURE);
                }
                if(wait(NULL) == -1) //czekaj na zakonczenie sie procesu potomnego
                {
                    perror("wait error"); //obsluga bledow funkcji wait
                    exit(EXIT_FAILURE);
                }
                break;
    }
    return 0;
}
