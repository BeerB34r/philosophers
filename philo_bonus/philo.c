/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   philo.c                                           :+:    :+:             */
/*                                                    +:+                     */
/*   By: mde-beer <mde-beer@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/01/04 02:51:58 by mde-beer     #+#    #+#                  */
/*   Updated: 2025/01/04 04:36:22 by mde-beer     ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>

void
	philosopher(
int id,
size_t start,
t_config config
)
{
	sem_t *const	talking_stick = sem_open(SEM_TALK, O_RDWR);
	sem_t *const	forks = sem_open(SEM_FORK, O_RDWR);

	if (sem_wait(talking_stick))
	{
		sem_close(talking_stick);
		sem_close(forks);
		exit(1);
	}
	sem_post(talking_stick);
	sem_close(talking_stick);
	while (!stop())
		if (think(id, start, config)
			|| grab(forks, id, start, config)
			|| eat(forks, id, start, config))
			break ;
	sem_close(forks);
	exit(0);
}

bool
	mitosis(
t_config config
)
{
	sem_t *const	talking_stick = sem_open(SEM_TALK, O_RDWR);
	pid_t			philo[MAX_PHILO];
	unsigned int	i;
	const size_t	start = get_time();

	sem_wait(talking_stick);
	i = -1;
	while (++i < config.count)
	{
		philo[i] = fork();
		if (philo[i] < 0)
		{
			while (i--)
				kill(philo[i], SIGCONT);
			sem_close(talking_stick);
			return (true);
		}
		else if (philo[i] == 0)
			philosopher(i + 1, start, config);
	}
	sem_post(talking_stick);
	sem_close(talking_stick);
	while (i--)
		waitpid(philo[i], NULL, 0);
	return (false);
}
