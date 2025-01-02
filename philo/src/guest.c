/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   guest.c                                             :+:    :+:           */
/*                                                      +:+                   */
/*   By: mde-beer <mde-beer@student.codam.nl>          +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/12/24 06:04:29 by mde-beer       #+#    #+#                */
/*   Updated: 2024/12/24 06:43:45 by mde-beer       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
#include <stdio.h>
#include <stdint.h>

void
	atomic_print_state(
const char *str,
t_philo *philo
)
{
	static size_t	start;
	static t_lock	printer = PTHREAD_MUTEX_INITIALIZER;

	pthread_mutex_lock(&printer);
	if (!start)
		start = get_time();
	pthread_mutex_lock(&philo->self);
	printf("%zu %i %s\n", get_time() - start, philo->pid, str);
	pthread_mutex_unlock(&philo->self);
	pthread_mutex_unlock(&printer);
}

bool
	die_or_print(
t_philo *const self,
const char *print
)
{
	static t_lock	deadlock = PTHREAD_MUTEX_INITIALIZER;
	static bool		finished = false;

	pthread_mutex_lock(&deadlock);
	if (finished)
		return (pthread_mutex_unlock(&deadlock), true);
	pthread_mutex_lock(&self->self);
	if (self->state == dead || self->last_meal < get_time() - self->chart.die)
	{
		finished = true;
		pthread_mutex_unlock(&self->self);
		atomic_print_state("has died", self);
		pthread_mutex_unlock(&deadlock);
		return (true);
	}
	pthread_mutex_unlock(&self->self);
	if (print)
		atomic_print_state(print, self);
	pthread_mutex_unlock(&deadlock);
	return (false);
}

void
	grab_fork(
t_philo *const self,
bool odd
)
{
	if (odd)
		pthread_mutex_lock(self->left);
	else
		pthread_mutex_lock(self->right);
	if (die_or_print(self, NULL))
	{
		pthread_mutex_unlock(self->left);
		pthread_mutex_unlock(self->right);
		return ;
	}
	die_or_print(self, "has taken a fork");
}

void
	eat(
t_philo *const self
)
{
	if (die_or_print(self, NULL))
		return ;
	grab_fork(self, self->pid % 2);
	if (die_or_print(self, NULL))
		return ;
	if (self->left == self->right)
	{
		reaper(self, SIZE_MAX);
		pthread_mutex_unlock(self->left);
		pthread_mutex_unlock(self->right);
		return ;
	}
	grab_fork(self, !(self->pid % 2));
	if (die_or_print(self, NULL))
		return ;
	set_eat(self);
	reaper(self, self->chart.eat + get_time());
	pthread_mutex_unlock(self->left);
	pthread_mutex_unlock(self->right);
	if (die_or_print(self, NULL) || self->count == self->chart.done)
		return ;
	set_sleep(self);
	reaper(self, self->chart.eep + get_time());
}

void
	*routine(
void *arg
)
{
	t_philo *const	self = (t_philo *)arg;
	bool			error;

	pthread_mutex_lock(gate());
	self->last_meal = get_time();
	if (self->state == dead)
		error = true;
	else
		error = false;
	pthread_mutex_unlock(gate());
	if (error)
		return (NULL);
	while (self->chart.done == 0 || self->count < self->chart.done)
	{
		if (die_or_print(self, "is thinking"))
			return (NULL);
		eat(self);
	}
	return (NULL);
}
