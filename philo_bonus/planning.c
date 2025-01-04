/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   planning.c                                        :+:    :+:             */
/*                                                    +:+                     */
/*   By: mde-beer <mde-beer@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/01/04 02:22:34 by mde-beer     #+#    #+#                  */
/*   Updated: 2025/01/04 04:01:58 by mde-beer     ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
#include <limits.h>
#include <fcntl.h>
#include <stddef.h>

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
		|| eep == ULONG_MAX || done == ULONG_MAX || count == 0
		|| count > MAX_PHILO)
		return (true);
	*config = (t_config){.count = count,
		.die = die,
		.eat = eat,
		.eep = eep,
		.done = done};
	return (false);
}

bool
	link_semaphores(
int fork_count
)
{
	sem_t			*talking_stick;
	sem_t			*forks;
	const mode_t	flags = (S_IRWXU | S_IRWXG | S_IRWXO);

	sem_unlink(SEM_TALK);
	sem_unlink(SEM_FORK);
	talking_stick = sem_open(SEM_TALK, O_CREAT, flags, 1);
	if (talking_stick == SEM_FAILED)
		return (true);
	sem_close(talking_stick);
	forks = sem_open(SEM_FORK, O_CREAT, flags, fork_count);
	if (forks == SEM_FAILED)
	{
		sem_unlink(SEM_TALK);
		return (true);
	}
	sem_close(forks);
	return (false);
}
