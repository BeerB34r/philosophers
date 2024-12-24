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

// the flipflop-while-chain (patent pending) at the end there starts at -1,
// then when it reaches config.count, will go backwards towards -1
// at which point it will flip back up toward config.count.
// yes, i know.

// TODO do some proper error handling in the case of threads failing
int
	main(
int argc,
char **argv
)
{
	t_config		config;
	t_lock			fork[MAX_PHILO];
	t_philo			philo[MAX_PHILO];
	unsigned int	i;

	if (argc < 5 || 6 < argc)
		return (usage(argv[0], "INVALID_PARAMETER_COUNT"));
	if (set_config(argc, argv, &config))
		return (printf("ERR: INVALID_PARAMETER(S)"));
	if (invite_guests(config, fork, philo))
		return (printf("ERR: MUTEX_INIT\n"));
	pthread_mutex_lock(gate());
	i = -1;
	while (++i < config.count)
		if (pthread_create(&philo[i].thread, NULL, routine, &philo[i]))
			return (printf("ERR: THREAD_CREATION\n"));
	pthread_mutex_unlock(gate());
	while (i--)
		if (pthread_join(philo[i].thread, NULL))
			return (printf("ERR: THREAD_EXIT\n"));
	while (++i < config.count)
	{
		pthread_mutex_destroy(&fork[i]);
		pthread_mutex_destroy(&philo[i].self);
	}
}
