/* Igor Tyszer,   Krakow 27.04.2021 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>


int main(int argc, char *argv[])
{
    if(argc != 3) //sprawdzenie, czy liczba argumentow jest prawidlowa, a jesli nie jest to wyswietl blad i zakoncz program
    {
        printf("Wpisana liczba argumentow jest nieprawidlowa\n");
        exit(EXIT_FAILURE);
    }
    
    int str[5];
    int wyjscie;
    int zwroconeBajty;
    int fd;
    
    if((fd = open(argv[1],O_RDONLY)) == -1) //otworzenie potoku nazwanego i zwrocenie jego deskryptoru
    {
        perror("pipe error"); // obsluga bledow funkcji pipe
        exit(EXIT_FAILURE);
    }
    
    if((wyjscie = open(argv[2],O_WRONLY)) == -1) //otworzenie pliku wyjsciowego i zwrocenie jego deskryptoru
    {
        perror("open error"); //obsluga bledow funkcji open
        exit(EXIT_FAILURE);
    }
    
    while((zwroconeBajty = read(fd, &str, 4))>0) //wykonuj dopóki czytanie str z potoku, porcja konsumenta to 4
    {
        sleep(2); //uspienie procesu na 2 sekundy
                    
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
    
    if(close(wyjscie) == -1) //zamknij deskryptor pliku wyjsciowego
    {
        perror("close error"); //obsluga bledow funkcji close
        exit(EXIT_FAILURE);
    }
    
    if(close(fd) == -1) //zamknij deskryptor potoku nazwanego
    {
        perror("close error"); //obsluga bledow funkcji close
        exit(EXIT_FAILURE);
    }
    return 0;
}
