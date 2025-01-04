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

size_t
	start_time(void)
{
	static size_t	start;

	if (!start)
		start = get_time();
	return (start);
}

int	
	reaper(
t_philo *const philo,
size_t sand
)
{
	sand += get_time();
	while (sand > get_time())
	{
		if (philo->chart->dead)
			return (1);
		if (famine(philo))
			return (1);
		usleep(INTERVAL);
	}
	return (0);
}

int
	stop_check(
t_philo *const philo
)
{
	return (philo->chart->dead || philo->chart->full == philo->chart.count)
}

int
	famine(
t_philo *const philo
)
{
	if (get_time() - philo->last_meal < philo->chart.die)
		return (0);
	pthread_mutex_lock(print());
	philo->chart->dead = true;
	printf(MSG_BASE, get_time() - start_time(), philo->pid, MSG_DEAD);
	pthread_mutex_unlock(print());
	return (1);
}
