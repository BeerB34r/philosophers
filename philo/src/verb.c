/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   verb.c                                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: mde-beer <mde-beer@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/01/03 22:18:50 by mde-beer     #+#    #+#                  */
/*   Updated: 2025/01/04 00:16:51 by mde-beer     ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
#include <stdint.h>

int
	think(
t_philo *const philo
)
{
	return (state_change(philo, thinking));
}

int	
	eat(
t_philo *const philo
)
{
	if (state_change(philo, eating) || reaper(philo, philo->chart.eat))
	{
		pthread_mutex_unlock(philo->left);
		pthread_mutex_unlock(philo->right);
		return (1);
	}
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(philo->right);
	if (philo->chart.done != 0 && ++philo->count == philo->chart.done)
		(*philo->chart.full)++;
	if (state_change(philo, sleeping) || reaper(philo, philo->chart.eep))
		return (1);
	return (0);
}

int
	grab(
t_philo *const philo
)
{
	return (grab_first(philo) || grab_second(philo));
}

int
	grab_first(
t_philo *const philo
)
{
	if (philo->pid % 2)
	{
		pthread_mutex_lock(philo->left);
		if (famine(philo) || state_change(philo, hungry))
		{
			pthread_mutex_unlock(philo->left);
			return (1);
		}
		return (0);
	}
	pthread_mutex_lock(philo->right);
	if (famine(philo) || state_change(philo, hungry))
	{
		pthread_mutex_unlock(philo->right);
		return (1);
	}
	return (0);
}

int
	grab_second(
t_philo *const philo
)
{
	if (philo->chart.count == 1)
	{
		pthread_mutex_unlock(philo->left);
		return (reaper(philo, SIZE_MAX), 1);
	}
	if (!(philo->pid % 2))
	{
		pthread_mutex_lock(philo->left);
		if (famine(philo) || state_change(philo, hungry))
		{
			pthread_mutex_unlock(philo->right);
			pthread_mutex_unlock(philo->left);
			return (1);
		}
		return (0);
	}
	pthread_mutex_lock(philo->right);
	if (famine(philo) || state_change(philo, hungry))
	{
		pthread_mutex_unlock(philo->left);
		pthread_mutex_unlock(philo->right);
		return (1);
	}
	return (0);
}
