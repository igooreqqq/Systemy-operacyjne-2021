/* Igor Tyszer,    Krakow 11.05.21 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include "biblioteka.h"

//tworzenie semafora
sem_t *nowySemafor(const char *name, int oflag, mode_t mode, unsigned int value)
{
    sem_t *sem;
    if((sem = sem_open(name, oflag, mode, value)) == SEM_FAILED)
    {
        perror("sem_open error"); //obsluga bledow funkcji sem_open
        exit(EXIT_FAILURE); 
    }
    return sem;
}

//otworzenie semafora
sem_t *otwarcieSemafora(const char *name, int oflag)
{
    sem_t *sem;
    if((sem = sem_open(name, oflag)) == SEM_FAILED)
    {
        perror("sem_open error"); //obsluga bledow funkcji sem_open
        exit(EXIT_FAILURE); 
    }
    return sem;
}

//uzyskanie wartosci semafora
void wartoscSemafora(sem_t *sem, int *sval)
{
    if(sem_getvalue(sem, sval) == -1)
    {
       perror("sem_getvalue error"); //obsluga bledow funkcji sem_getvalue
        exit(EXIT_FAILURE); 
    }
}

//podniesienie semafora
void podniesienieSemafora(sem_t *sem)
{
    if(sem_post(sem) == -1)
    {
        perror("sem_post error"); //obsluga bledow funkcji sem_post
        exit(EXIT_FAILURE); 
    }
}

//opuszczenie semafora
void opuszczenieSemafora(sem_t *sem)
{
    if(sem_wait(sem) == -1)
    {
        perror("sem_wait error"); //obsluga bledow funkcji sem_wait
        exit(EXIT_FAILURE); 
    }
}

//zamykanie semafora
void zamykanieSemafora(sem_t *sem)
{
    if(sem_close(sem) == -1)
    {
        perror("sem_close error"); //obsluga bledow funkcji sem_close
        exit(EXIT_FAILURE); 
    }
}

//usuniecie semafora
void usuniecieSemafora(const char *name)
{
    if(sem_unlink(name) == -1)
    {
        perror("sem_unlink error"); //obsluga bledow funkcji sem_unlink
        exit(EXIT_FAILURE); 
    }
}
