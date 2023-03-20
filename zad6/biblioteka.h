/* Igor Tyszer,    Krakow 11.05.21 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>

//tworzenie semafora
sem_t *nowySemafor(const char *name, int oflag, mode_t mode, unsigned int value);

//otworzenie semafora
sem_t *otwarcieSemafora(const char *name, int oflag);

//uzyskanie wartosci semafora
void wartoscSemafora(sem_t *sem, int *sval);

//podniesienie semafora
void podniesienieSemafora(sem_t *sem);

//opuszczenie semafora
void opuszczenieSemafora(sem_t *sem);

//zamykanie semafora
void zamykanieSemafora(sem_t *sem);

//usuniecie semafora
void usuniecieSemafora(const char *name);

