/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   philo.c                                           :+:    :+:             */
/*                                                    +:+                     */
/*   By: mde-beer <mde-beer@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/01/03 21:58:02 by mde-beer     #+#    #+#                  */
/*   Updated: 2025/01/03 23:28:43 by mde-beer     ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
#include <stdio.h>
#include <stdint.h>

void
	*philosopher(
void *arg
)
{
	t_philo *const	self = (t_philo *)arg;
	static size_t	start_time;

	pthread_mutex_lock(gate());
	if (!start_time)
		start_time = get_time();
	self->start = start_time;
	self->last_meal = self->start;
	pthread_mutex_unlock(gate());
	while (!stop(self->chart))
		if (think(self) || grab(self) || eat(self))
			break ;
	return (NULL);
}

void
	*monitoring(
void *arg
)
{
	t_philo		*philo;
	t_config	config;
	int			i;

	philo = (t_philo *)arg;
	config = philo[0].chart;
	i = -1;
	pthread_mutex_lock(gate());
	pthread_mutex_unlock(gate());
	while (!stop(config))
	{
		i = (i + 1) % config.count;
		check_health(&philo[i], config);
	}
	return (NULL);
}

void
	check_health(
t_philo *const philo,
t_config config
)
{
	if (philo->last_meal == SIZE_MAX)
		return ;
	if (get_time() - philo->last_meal <= config.die)
		return ;
	pthread_mutex_lock(print());
	if (*(config.dead))
	{
		pthread_mutex_unlock(print());
		return ;
	}
	*(config.dead) = true;
	printf(MSG_BASE, get_time() - philo->start, philo->pid, MSG_DEAD);
	pthread_mutex_unlock(print());
}

int
	stop(
t_config config
)
{
	return ((*(config.dead) || *(config.full) == config.count));
}

int	
	state_change(
t_philo *const philo,
enum e_state state
)
{
	char			*msg;
	int				ret;

	if (state == thinking)
		msg = MSG_THINK;
	else if (state == hungry)
		msg = MSG_FORK;
	else if (state == eating)
		msg = MSG_EAT;
	else if (state == sleeping)
		msg = MSG_SLEEP;
	pthread_mutex_lock(print());
	pthread_mutex_lock(&philo->self);
	ret = stop(philo->chart);
	if (!ret)
		printf(MSG_BASE, get_time() - philo->start, philo->pid, msg);
	philo->state = state;
	if (state == eating)
		philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->self);
	pthread_mutex_unlock(print());
	return (ret);
}
