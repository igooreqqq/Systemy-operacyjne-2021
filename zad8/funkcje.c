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

#include "funkcje.h"

mqd_t stworzKolejke(const char *name, int oflag, mode_t mode, struct mq_attr *attr)
{
    mqd_t open;
    if((open = mq_open(name, oflag, mode, attr)) == -1)
    {
        perror(" mq_open error");
        _exit(EXIT_FAILURE);
    }
    return open;
}

mqd_t otworzKolejke(const char *name, int oflag)
{
    mqd_t open;
    if((open = mq_open(name, oflag)) == -1)
    {
        perror(" mq_open error");
        _exit(EXIT_FAILURE);
    }
    return open;
}

int wyslijKomunikat(mqd_t mqdes, const char *msg_ptr, size_t msg_len, unsigned int msg_prio)
{
    int value;
    if((value = mq_send(mqdes, msg_ptr, msg_len, msg_prio)) == -1)
    {
        perror(" mq_send error");
        _exit(EXIT_FAILURE);
    }
    return value;
}

int odbierzKomunikat(mqd_t mqdes, char *msg_ptr, size_t msg_len, unsigned int *msg_prio)
{
    int value;
    if((value = mq_receive(mqdes, msg_ptr, msg_len, msg_prio)) == -1)
    {
        perror(" mq_receive error");
        _exit(EXIT_FAILURE);
    }
    return value;
}

void zamknijKolejke(mqd_t mqdes)
{
    if(mq_close(mqdes) == -1)
    {
        perror(" mq_close error");
        _exit(EXIT_FAILURE);
    }
}

void usunKolejke(const char *name)
{
    if(mq_unlink(name) == -1)
    {
        perror(" mq_unlink error");
        _exit(EXIT_FAILURE);
    }
}
