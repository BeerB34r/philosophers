/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   main.c                                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: mde-beer <mde-beer@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/01/04 02:20:20 by mde-beer     #+#    #+#                  */
/*   Updated: 2025/01/04 04:07:08 by mde-beer     ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
#include <stdio.h>

int
	main(
int argc,
char **argv
)
{
	t_config	config;

	if (argc < 5 || 6 < argc)
		return (usage(argv[0], "INVALID_PARAMETER_COUNT\n"));
	if (set_config(argc, argv, &config))
		return (error("INVALID_PARAMETER(S)\n", 2));
	if (link_semaphores(config.count))
		return (error("SEMAPHORE_INIT\n", 3));
	if (mitosis(config))
		return (unlink_semaphores(), error("FORK_FAILURE\n", 4));
	unlink_semaphores();
	printf("\nSimulation complete\n");
}
