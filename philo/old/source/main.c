/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   main.c                                              :+:    :+:           */
/*                                                      +:+                   */
/*   By: mde-beer <mde-beer@student.codam.nl>          +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/12/19 17:39:11 by mde-beer       #+#    #+#                */
/*   Updated: 2024/12/20 15:29:22 by mde-beer       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static int
	usage(
const char *bin_name,
const char *error
)
{
	printf("%s\n", error);
	printf("Usage: %s %s\n", bin_name, USAGE);
	return (1);
}

int	
	set(
int argc,
char **argv
)
{
	t_party *const	party = ph_calloc(1, sizeof(t_party));

	if (!party)
		return (error(1));
	*party = (t_party){.guestlist = ph_atoi(argv[1]), 
						.sands_of_time = ph_atoi(argv[2]),
						.slipperiness = ph_atoi(argv[3]),
						.heftiness = ph_atoi(argv[4]),
						.sentence_len = 0
						}
	if (argc == 6)
		party->sentence_len = ph_atoi(argv[5]);
	if (set_table(party->guestlist, &party->utensils))
		return (error(1));
	if (seat_guests(party->guestlist, &party->guests))
		return (error(1));
	return (butler(party), 0);
}

int	
	ready(
int argc,
char **argv
)
{
	int	i;

	if (argc < 5 || 6 < argc)
		return (usage(argv[0], "Invalid argument count"));
	i = 0;
	while (++i < argc)
		if (validate_input(argv[i]))
			return (usage(argv[0], "Invalid argument format"));
	return (0);
}

int	
	main(
int argc,
char **argv
)
{
	if (ready(argc, argv))
		return (1);
	if (set(argc, argv))
		return (1);
	return (go());
}
