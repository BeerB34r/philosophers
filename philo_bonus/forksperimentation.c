/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   forksperimentation.c                                :+:    :+:           */
/*                                                      +:+                   */
/*   By: mde-beer <mde-beer@student.codam.nl>          +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/12/24 07:12:07 by mde-beer       #+#    #+#                */
/*   Updated: 2024/12/24 14:23:05 by mde-beer       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */


// the semaphore suite
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <unistd.h>
#include <semaphore.h>
#include <signal.h>
#include <pthread.h>

#include <stdio.h>
#include <errno.h>
#include <string.h>

#define FORKS "/forks"
#define MAX_PHILO 200
#define TIMEOUT 10000
#define INTERVAL 100

size_t
	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

//void
	//reaper(
//t_philo *const self,
//size_t sand
//)
//{
	//while (sand > get_time())
	//{
		//if (dead(self))
			//return ;
		//usleep(INTERVAL);
	//}
//}
//
int
	touch_forks(
int action,
int extra
)
{
	sem_t	*forks;

	if (action == 1)
	{
		sem_unlink(FORKS);
		forks = sem_open(FORKS, O_CREAT, (S_IRWXU | S_IRWXG | S_IRWXO), extra);
		if (forks == SEM_FAILED)
			return (printf("fork touch failed\n"), 1);
		return (0);
	}
	else if (action == 2)
	{
		sem_close(forks);
		sem_unlink(FORKS);
	}
	return (0);
}

void
	putstate(
const char *format,
int arg,
sem_t *semaphore
)
{
	sem_wait(semaphore);
	printf("%zu ", get_time());
	printf(format, arg);
	sem_post(semaphore);
}

void
	*grab_forks(
void	*arg
)
{
	sem_t *const	forks = sem_open(FORKS, O_RDWR);
	sem_t *const	talking_stick = sem_open("/talking_stick", O_RDWR);
	const long long	id = (long long)arg;

	if (sem_wait(forks))
		return (printf("lmao\n"), sem_close(talking_stick), (void *)1);
	putstate("%lld first spoon get\n", id, talking_stick);
	if (sem_wait(forks))
		return (putstate("%lld spoon dropped\n", id, talking_stick), sem_close(talking_stick), sem_post(forks), (void *)1);
	putstate("%lld second spoon get\n", id, talking_stick);
	sem_close(forks);
	sem_close(talking_stick);
	return ((void *)0);
}

int
	try_grab(
long long id
)
{
	pthread_t	thread;
	int			*status;

	if (pthread_create(&thread, NULL, grab_forks, (void *)id))
		return (printf("thread_err"));
	usleep(TIMEOUT);
	kill(0, SIGCONT);
	if (pthread_join(thread, (void **)&status))
		return (printf("thred_err"));
	if (status)
		return (1);
	return (0);
}

int
	child(
long long id
)
{
	sem_t *const	talking_stick = sem_open("/talking_stick", O_RDWR);
	sem_t *const	forks = sem_open(FORKS, O_RDWR);

	sem_wait(talking_stick);
	sem_post(talking_stick);
	putstate("%d is thinking\n", id, talking_stick);
	if (forks == SEM_FAILED)
		return (printf("fork failed\n"));
	while (try_grab(id))
		printf("fork off\n");
	putstate("%lld yummers\n", id, talking_stick);
	sem_post(forks);
	sem_post(forks);
	sem_close(forks);
	putstate("%lld finished\n", id, talking_stick);
	sem_close(talking_stick);
	return (0);
}

int
	main(
int argc,
char **argv
)
{
	pid_t			pid[MAX_PHILO];
	sem_t 			*talking_stick;
	long long		i;

	touch_forks(1, 10);
	sem_unlink("/talking_stick");
	talking_stick = sem_open("/talking_stick", O_CREAT, (S_IRWXU | S_IRWXG | S_IRWXO), 1);
	if (talking_stick == SEM_FAILED)
		return (printf("ERR: SEMAPHORE\n"));
	i = -1;
	sem_wait(talking_stick);
	while (++i < 10)
	{
		pid[i] = fork();
		if (pid[i] < 0)
			return (printf("ERR: FORK\n"));
		else if (pid[i] == 0)
			return (child(i));
	}
	printf("let loose\n");
	sem_post(talking_stick);
	while (i--)
		waitpid(-1, NULL, 0); // implement kill-all if return is garbage
	sem_close(talking_stick);
	sem_unlink("/talking_stick");
	touch_forks(2, 0);
}
