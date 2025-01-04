/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   new_guest.c                                       :+:    :+:             */
/*                                                    +:+                     */
/*   By: mde-beer <mde-beer@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/01/02 19:28:16 by mde-beer     #+#    #+#                  */
/*   Updated: 2025/01/02 19:30:23 by mde-beer     ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void
	*philosopher(
void *arg
)
{
	t_philo *const	self = (t_philo *)arg;

	pthread_mutex_lock(gate());
	self->last_meal = get_time();
	pthread_mutex_unlock(gate());
	while (!stop_check(self))
		if (think(self) || grab(self) || eat(self))
			break ;
	return (NULL);
}

void
	*monitor(
void *arg
)
{
	t_philo
}

int	
	think(
t_philo *const philo
)
{
	if (state_change(philo, thinking))
		return (1);
	return (0);
}

int	
	grab(
t_philo *const philo
)
{
	if (grab_first(philo) || grab_last(philo))
		return (1);
	return (0);
}

int	
	eat(
t_philo *const philo
)
{
	if (state_change(philo, eating) || reaper(philo, philo->chart.eat))
		return (1);
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(philo->right);
	if (philo->chart.done != 0 && ++philo->count == philo->chart.done)
		philo->chart->full++;
	if (state_change(philo, sleeping) || reaper(philo, philo->chart.sleep))
		return (1);
	return (0);
}
