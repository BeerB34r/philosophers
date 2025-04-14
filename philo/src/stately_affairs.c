/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   stately_affairs.c                                   :+:    :+:           */
/*                                                      +:+                   */
/*   By: mde-beer <mde-beer@student.codam.nl>          +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/12/24 06:21:54 by mde-beer       #+#    #+#                */
/*   Updated: 2024/12/24 06:35:43 by mde-beer       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdint.h>
#include <stdio.h>

t_lock
	*gate(void)
{
	static t_lock	gate = PTHREAD_MUTEX_INITIALIZER;

	return (&gate);
}

t_lock
	*print(void)
{
	static t_lock	print = PTHREAD_MUTEX_INITIALIZER;

	return (&print);
}

size_t
	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	
	reaper(
t_philo *const philo,
size_t sand
)
{
	if (sand != SIZE_MAX)
		sand += get_time();
	while (sand > get_time())
	{
		if (*(philo->chart.dead) || famine(philo))
			return (1);
		usleep(INTERVAL);
	}
	return (0);
}

int
	famine(
t_philo *const philo
)
{
	pthread_mutex_lock(&philo->self);
	if (get_time() - philo->last_meal <= philo->chart.die)
		return (pthread_mutex_unlock(&philo->self), 0);
	pthread_mutex_lock(print());
	if (*(philo->chart.dead))
	{
		pthread_mutex_unlock(print());
		pthread_mutex_unlock(&philo->self);
		return (1);
	}
	*(philo->chart.dead) = true;
	printf(MSG_BASE, get_time() - philo->start, philo->pid, MSG_DEAD);
	pthread_mutex_unlock(print());
	pthread_mutex_unlock(&philo->self);
	return (1);
}
