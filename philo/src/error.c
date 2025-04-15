/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   error.c                                           :+:    :+:             */
/*                                                    +:+                     */
/*   By: mde-beer <mde-beer@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/01/02 12:03:44 by mde-beer     #+#    #+#                  */
/*   Updated: 2025/01/03 23:32:09 by mde-beer     ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
#include <unistd.h>
#include <stdio.h>

static int
	strlen(
const char *str
)
{
	int	i;

	i = -1;
	while (str[++i])
		;
	return (i);
}

int
	error(
const char *message,
const int code
)
{
	const int	len = strlen(message);

	write(2, "ERR: ", 5);
	write(2, message, len);
	return (code);
}

int
	usage(
const char *bin,
const char *err
)
{
	error(err, 0);
	printf("USAGE: %s %s\n", bin, USAGE);
	return (1);
}

void
	mutex_clean(
int count,
t_philo philo[MAX_PHILO]
)
{
	while (count >= 0)
	{
		pthread_mutex_destroy(&philo[count].self);
		pthread_mutex_destroy(philo[count--].left);
	}
}

void
	premature_death(
int count,
t_config config,
t_philo philo[MAX_PHILO]
)
{
	*(config.dead) = true;
	gate(false);
	while (count >= 0)
		pthread_join(philo[count--].thread, NULL);
}
