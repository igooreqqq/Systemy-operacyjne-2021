/* Igor Tyszer,   Krakow 23.05.21 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <signal.h>
#include <mqueue.h>

//funkcja tworzaca kolejke
mqd_t stworzKolejke(const char *name, int oflag, mode_t mode, struct mq_attr *attr);

//funkcja otwierajaca kolejke
mqd_t otworzKolejke(const char *name, int oflag);

//funcka wysylajaca komunikat
int wyslijKomunikat(mqd_t mqdes, const char *msg_ptr, size_t msg_len, unsigned int msg_prio);

//funkcja odbierajaca komunikat
int odbierzKomunikat(mqd_t mqdes, char *msg_ptr, size_t msg_len, unsigned int *msg_prio);

//funkcja zamykaja kolejke
void zamknijKolejke(mqd_t mqdes);

//funkcja usuwaja kolejke
void usunKolejke(const char *name);
