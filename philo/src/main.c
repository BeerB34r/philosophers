/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   main.c                                              :+:    :+:           */
/*                                                      +:+                   */
/*   By: mde-beer <mde-beer@student.codam.nl>          +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/12/24 04:57:27 by mde-beer       #+#    #+#                */
/*   Updated: 2024/12/24 06:38:06 by mde-beer       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
#include <stdio.h>
#include <stdlib.h>

// the flipflop-while-chain (patent pending) at the end there starts at -1,
// then when it reaches config.count, will go backwards towards -1
// at which point it will flip back up toward config.count.
// yes, i know.

// TODO: do some proper error handling in the case of threads failing
int
	main(
int argc,
char **argv
)
{
	t_config		config;
	pthread_t		monitor;
	t_lock			fork[MAX_PHILO];
	t_philo			philo[MAX_PHILO];
	unsigned int	i;

	if (argc < 5 || 6 < argc)
		return (usage(argv[0], "INVALID_PARAMETER_COUNT\n"));
	if (set_config(argc, argv, &config))
		return (error("INVALID_PARAMETER(S)\n", 1));
	if (!config.full || !config.dead)
		return (free(config.full), free(config.dead), error("ALLOC_FAIL\n", 2));
	if (invite_guests(config, fork, philo))
		return (error("MUTEX_INIT\n", 3));
	if (seat_guests(config, philo, &monitor))
		return (error("THREAD_CREATION\n", 4));
	i = -1;
	while (++i < config.count)
		pthread_join(philo[i].thread, NULL);
	pthread_join(monitor, NULL);
	while (i--)
		pthread_mutex_destroy(&fork[i]);
	while (++i < config.count)
		pthread_mutex_destroy(&philo[i].self);
	return (free(config.full), free(config.dead), 0);
}
