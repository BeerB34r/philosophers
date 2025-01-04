/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   verb.c                                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: mde-beer <mde-beer@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/01/04 03:38:14 by mde-beer     #+#    #+#                  */
/*   Updated: 2025/01/04 04:24:32 by mde-beer     ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
#include <unistd.h>

bool
	think(
int id,
size_t start
)
{
	putstate("%i is thinking\n", id, start);
	return (false);
}

bool
	grab(
sem_t *forks,
int id,
size_t start
)
{
	sem_wait(forks);
	putstate("%i has taken a fork\n", id, start);
	sem_wait(forks);
	putstate("%i has taken a fork\n", id, start);
	return (false);
}

bool
	eat(
sem_t *forks,
int id,
size_t start
)
{
	putstate("%i is eating\n", id, start);
	usleep(1000 * 1000);
	sem_post(forks);
	sem_post(forks);
	putstate("%i is sleeping\n", id, start);
	usleep(1000 * 1000);
	return (false);
}

bool
	stop(void)
{
	return (false);
}
