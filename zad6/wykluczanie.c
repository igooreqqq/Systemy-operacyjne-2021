/* Igor Tyszer,    Krakow 11.05.21 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <string.h>
#include "biblioteka.h"
#include <time.h>

#define nazwaSemafora "/Semafor"

sem_t *sem;
void *p = &sem;
char str[1];
char str2[12];
int wejscie;
int zwroconeBajty;

int main(int argc, char *argv[])
{
    if(argc != 3) //sprawdzenie, czy liczba argumentow jest prawidlowa, a jesli nie jest to wyswietl blad i zakoncz program
    {
        printf("Wpisana liczba argumentow jest nieprawidlowa, w argumentach nalezy umiescic: wykluczanie.x <plik tekstowty> <ilosc SK>\n");
        exit(EXIT_FAILURE);
    }
    
    sem = otwarcieSemafora(nazwaSemafora,O_RDWR); //funkcja otwierajaca utworzony wczesniej semafor
    
    int val;
    
    wartoscSemafora(sem, &val); //funkcja sprawdzajaca aktualna wartosc semafora

    int randomTime = 2 + rand() % (5);
    sleep(randomTime); //uspij proces na losowy czas w zakresie od 2 do 6 sekund
    
    printf("Przed sekcja krytyczna. PID: %d, wartosc semafora to: %d\n",getpid(),val);
    
    int iloscSekcji;
    iloscSekcji = atoi(argv[2]);
    
    for(int j = 0; j < iloscSekcji; j++)
    {
        opuszczenieSemafora(sem); //funkcja opuszczajaca semafor
        
        wartoscSemafora(sem, &val); //funkcja sprawdzajaca aktualna wartosc semafora
        
        printf("        Podczas sekcji krytycznej. PID: %d, wartosc semafora to: %d\n",getpid(),val);
        
        if((wejscie = open(argv[1],O_RDONLY)) == -1) //otworzenie pliku wejsciowego i zwrocenie jego deskryptoru
                {
                    perror("open error"); //obsluga bledow funkcji open
                    exit(EXIT_FAILURE);
                }
                zwroconeBajty = read(wejscie, &str, 1);
        
                printf("        Proces o PID: %d wchodzi do sekcji krytycznej nr: %d\n",getpid(),j+1);
                printf("        Proces o PID: %d pobiera z pliku: %c\n",getpid(),str[0]);
        
                int numer;
                numer = atoi(str);
                numer++;
                
                printf("        Proces o PID: %d zwiekszyl numer: %d i zapisuje go do pliku\n",getpid(),numer);
                
                if(close(wejscie) == -1) //zamkniecie deskryptoru wejscia
                {
                    perror("close error"); //obsluga bledow funkcji close
                    exit(EXIT_FAILURE);
                }
                
                int randomTime = 2 + rand() % (5);
                sleep(randomTime); //uspij proces na losowy czas w zakresie od 2 do 6 sekund
                
                sprintf(str2,"%d",numer);
                if((wejscie = open(argv[1],O_WRONLY)) == -1) //otworzenie pliku wejsciowego i zwrocenie jego deskryptoru
                {
                    perror("open error"); //obsluga bledow funkcji open
                    exit(EXIT_FAILURE);
                }
                    
                if(write(wejscie,&str2[0],1) == -1) //zapisanie do potoku danych odczytanych z deskryptora wejscia
                {
                    perror("write error"); //obsluga bledow funkcji write
                    exit(EXIT_FAILURE);
                }
                
                if(close(wejscie) == -1) //zamkniecie deskryptoru wejscia
                {
                    perror("close error"); //obsluga bledow funkcji close
                    exit(EXIT_FAILURE);
                }
                
        podniesienieSemafora(sem); //funkcja podnoszaca semafor
        
        wartoscSemafora(sem, &val); //funkcja sprawdzajaca aktualna wartosc semafora
        
        printf("Po sekcji krytycznej. PID: %d, a wartosc semafora to: %d\n",getpid(),val);
    }
    
    zamykanieSemafora(sem); //funkcja ktora zamyka otwarty wczesniej semafor
}
