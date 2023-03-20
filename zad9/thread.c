/* Igor Tyszer,                                         Krakow 02.06.21
 * W programie przy pomocy muteksow zaimplementowano zadanie wzajemnego
     wykluczania dla watkow. Dla zademonstrowania operacji
     na zasobie dzielonym uzyto wspolnej globalnej zmiennej licznikowej, 
     ktorej wartosc jest zwracana przed zakonczeniem programu. */

#define _REENTRANT

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <signal.h>
#include <pthread.h>
#include <time.h>

int iloscWatkow;
int iloscCykli;
pthread_mutex_t mutex; //utworzenie mutexu o nazwie 'mutex'
void *p = &mutex;

int licznik_globalny = 0;

void gotoxy(unsigned x, unsigned y) //funkcja ktora umieszcza wskaznik na pozycji o wspolrzednych (x,y)
{
    printf("\033[%d;%dH\033[2K", y, x);
}

void *print(void *arg) //funkcja wywolywana przez funkcje pthread_create
{
    sleep(1);
    int licznik;
    int *i = (int *)arg; // i oznacza numer watku
    for(int j = 1; j < iloscCykli + 1; j++)
    {
        int randomTime = 1 + rand() % (3);
        sleep(randomTime); //uspij proces na losowy czas z zakresie od 1 do 4 sekund
        pthread_mutex_lock(&mutex); //funkcja ta zamyka muteks
        licznik = licznik_globalny;
        licznik++;
        if(j == (iloscCykli)) //przypadek dla ostatniej sekcji krytycznej
        {
            
            gotoxy(40, iloscWatkow + 2 + *i);     printf("Watek nr: %d w sekcji krytycznej: %d\n", *i, j);
            int randomTime = 1 + rand() % (3);
            sleep(randomTime); //uspij proces na losowy czas z zakresie od 1 do 4 sekund
            gotoxy(1, iloscWatkow + 2 + *i);     
            printf("\033[7m");     // Wlacz migotanie i odwrotny obraz
            printf("Watek nr: %d SKONCZYLEM!\n", *i);
            printf("\033[0m");       // Wroc do domyslnego trybu wyswietlania
        }
        else //pozostale przypadki
        {
            
            gotoxy(40, iloscWatkow + 2 + *i);     printf("Watek nr: %d w sekcji krytycznej: %d\n", *i, j);
            int randomTime = 1 + rand() % (3);
            sleep(randomTime); //uspij proces na losowy czas z zakresie od 1 do 4 sekund
            gotoxy(1, iloscWatkow + 2 + *i);     printf("Watek nr: %d, sekcja prywatna nr: %d\n", *i, j+1);
        }
        licznik_globalny = licznik;
        pthread_mutex_unlock(&mutex); //funkcja otwierajaca muteks
    }
    free(arg); //zwolnienie pamieci
    pthread_exit(0); //konczy prace watku
}

int main(int argc, char *argv[])
{
    if( argc != 3) //sprawdzenie, czy liczba argumentow jest prawidlowa, a jesli nie jest to wyswietl blad i zakoncz program
    {
        printf("Wpisana liczba argumentow jest nieprawidlowa, nalezy podac liczbe watkow i ilosc sekcji krytycznych!\n");
        exit(EXIT_FAILURE);
    }
    
    system("clear"); //wyczysc ekran konsoli
    printf("Zainicjowano muteks o adresie: %p\n\n", p);
    
    printf("\033[5;7m");     // Wlacz migotanie i odwrotny obraz
    printf("    ---- Nacisnij klawisz [Enter], aby wystartowac! ----   ");
    getchar();
    printf("\033[0m");       // Wroc do domyslnego trybu wyswietlania
    
    iloscWatkow = atoi(argv[1]);
    iloscCykli = atoi(argv[2]);
    srand(time(NULL));
    
    system("clear"); //wyczysc ekran konsoli
    
    int i;
    
    pthread_t t[iloscWatkow];
    
    for( i = 0; i < iloscWatkow; i++)
    {
        int* arg = malloc(sizeof(int)); //przydzielenie pamieci
        *arg = i;
        pthread_create(&t[i], NULL, &print, arg); //dodaje do procesu nowy watek wykonania, 
                                                  //w argumentach przykazywana funkcja print a takze numer watku     
                                                  
        printf("Utworzono watek nr %d o ID: %ld\n", i, t[i]);
    }
    
    printf("\n");
    
    for( i = 0; i < iloscWatkow; i++)
    {
        printf("Watek nr: %d, sekcja prywatna nr: 1\n", i);
    }
    
    for( i = 0; i < iloscWatkow; i++)
    {
        pthread_join( t[i], NULL); //czekaj na zakonczenie watku
    }
    
    sleep(2);
    
    gotoxy(1, 2*iloscWatkow + 3);       printf("Licznik = %d\n", licznik_globalny);
    gotoxy(1, 2*iloscWatkow + 4);       printf("Licznik powinien byc = %d\n", iloscWatkow * iloscCykli);
    
    if(pthread_mutex_destroy(&mutex) == 0) //usuniecie muteksu
    {
        gotoxy(1, 2*iloscWatkow + 5); printf("Poprawnie usunieto muteks o adresie %p\n", p);
    }
    
    return 0;
}
