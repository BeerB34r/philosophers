/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   stately_affairs.c                                 :+:    :+:             */
/*                                                    +:+                     */
/*   By: mde-beer <mde-beer@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/01/04 01:51:45 by mde-beer     #+#    #+#                  */
/*   Updated: 2025/01/04 04:23:21 by mde-beer     ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
#include <stdio.h>
#include <sys/time.h>
#include <semaphore.h>
#include <fcntl.h>

size_t
	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void
	putstate(
const char *format,
int arg,
size_t start
)
{
	sem_t *const	talking_stick = sem_open("/talking_stick", O_RDWR);

	sem_wait(talking_stick);
	printf("%zu ", get_time() - start);
	printf(format, arg);
	sem_post(talking_stick);
	sem_close(talking_stick);
}

void
	unlink_semaphores(void)
{
	sem_unlink(SEM_TALK);
	sem_unlink(SEM_FORK);
}


