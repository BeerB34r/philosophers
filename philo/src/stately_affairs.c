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

size_t
	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void
	reaper(
t_philo *const self,
size_t sand
)
{
	while (sand > get_time())
	{
		if (die_or_print(self, NULL))
			return ;
		usleep(INTERVAL);
	}
}

void
	set_eat(
t_philo *const self
)
{
	pthread_mutex_lock(&self->self);
	self->last_meal = get_time();
	self->state = eating;
	self->count++;
	pthread_mutex_unlock(&self->self);
	die_or_print(self, "is eating");
}

void
	set_sleep(
t_philo *const self
)
{
	pthread_mutex_lock(&self->self);
	self->state = sleeping;
	pthread_mutex_unlock(&self->self);
	die_or_print(self, "is sleeping");
}
