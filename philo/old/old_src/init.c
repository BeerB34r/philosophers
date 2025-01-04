/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   init.c                                              :+:    :+:           */
/*                                                      +:+                   */
/*   By: mde-beer <mde-beer@student.codam.nl>          +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/12/24 05:19:29 by mde-beer       #+#    #+#                */
/*   Updated: 2024/12/24 07:06:20 by mde-beer       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <stdint.h>

static int
	ph_inlimset(
int c,
const char *set,
int lim
)
{
	int	i;

	i = -1;
	while (set[++i] && i < lim)
		if (c == set[i])
			return (i);
	return (-1);
}

static unsigned long
	ph_atoi(
const char *str
)
{
	unsigned long	out;
	int				i;

	out = 0;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	while (str[i] && ph_inlimset(str[i], RADIX, BASE) != -1)
	{
		out = out * BASE + ph_inlimset(str[i++], RADIX, BASE);
		if (out > UINT_MAX)
			return (ULONG_MAX);
	}
	if (!out)
		return (ULONG_MAX);
	return (out);
}

bool
	set_config(
int argc,
char **argv,
t_config *config
)
{
	const unsigned long	count = ph_atoi(argv[1]);
	const unsigned long	die = ph_atoi(argv[2]);
	const unsigned long	eat = ph_atoi(argv[3]);
	const unsigned long	eep = ph_atoi(argv[4]);
	unsigned long		done;

	if (argc == 6)
		done = ph_atoi(argv[5]);
	else
		done = 0;
	if (count == ULONG_MAX || die == ULONG_MAX || eat == ULONG_MAX
		|| eep == ULONG_MAX || done == ULONG_MAX || count == 0)
		return (true);
	*config = (t_config){.count = count,
		.die = die,
		.eat = eat,
		.eep = eep,
		.done = done};
	return (false);
}

bool
	invite_guests(
t_config config,
t_lock fork[MAX_PHILO],
t_philo philo[MAX_PHILO]
)
{
	unsigned int	i;

	i = -1;
	while (++i < config.count)
	{
		if (pthread_mutex_init(&fork[i], NULL) || \
			pthread_mutex_init(&philo[i].self, NULL))
		{
			while (i >= 0)
			{
				pthread_mutex_destroy(&fork[i]);
				pthread_mutex_destroy(&philo[i--].self);
			}
			return (true);
		}
		philo[i].pid = i + 1;
		philo[i].left = &fork[i];
		philo[i].right = &fork[(i + 1) % config.count];
		philo[i].last_meal = SIZE_MAX;
		philo[i].count = 0;
		philo[i].chart = config;
		philo[i].state = thinking;
	}
	return (false);
}

bool
	seat_guests(
t_config config,
t_philo philo[MAX_PHILO]
)
{
	int	i;
	int	j;

	i = -1;
	pthread_mutex_lock(gate());
	while (++i < config.count)
	{
		if (pthread_create(&philo[i].thread, NULL, philosopher, &philo[i]))
		{
			j = i;
			while (j)
				philo[--j].state = dead;
			pthread_mutex_unlock(gate());
			while (i)
				pthread_join(philo[--i].thread, NULL);
			while (i < config.count)
			{
				pthread_mutex_destroy(&philo[i].left);
				pthread_mutex_destroy(&philo[i++]);
			}
			return (true);
		}
	}
	pthread_mutex_unlock(gate());
	return (false);
}
