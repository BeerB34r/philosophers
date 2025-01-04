/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   manners.c                                         :+:    :+:             */
/*                                                    +:+                     */
/*   By: mde-beer <mde-beer@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/01/03 20:11:38 by mde-beer     #+#    #+#                  */
/*   Updated: 2025/01/03 21:22:08 by mde-beer     ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

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
	grab_last(
t_philo *const philo
)
{
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

int	
	state_change(
t_philo *const philo,
enum e_state state
)
{
	static size_t	start;
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
	if (!start)
		start = get_time();
	ret = stop_check(philo);
	if (!ret)
		printf(MSG_BASE, get_time() - start, philo->pid, msg);
	philo->state = state;
	pthread_mutex_unlock(&philo->self);
	pthread_mutex_unlock(print());
	return (ret);
}
