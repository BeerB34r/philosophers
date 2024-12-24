/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   temporality.c                                       :+:    :+:           */
/*                                                      +:+                   */
/*   By: mde-beer <mde-beer@student.codam.nl>          +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/12/03 18:09:28 by mde-beer       #+#    #+#                */
/*   Updated: 2024/12/19 15:26:45 by mde-beer       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <philo.h>

t_imestamp
	clock(
t_imestamp *time
)
{
	static t_imestamp	start_time = {0};

	if (time)
		start_time = *time;
	return (start_time);
}

t_imestamp
	timestamp(void)
{
	t_imestamp	clock;

	gettimeofday(&clock, NULL);
	return (clock);
}

int	
	elapsed_time(
t_imestamp end,
t_imestamp start,
t_imestamp *elapsed
)
{
	int	nsec;

	if (start.tv_usec < end.tv_usec)
	{
		nsec = (end.tv_usec - start.tv_usec) / 1000000 + 1;
		end.tv_usec -= 1000000 * nsec;
		end.tv_sec += nsec;
	}
	if (start.tv_usec - end.tv_usec > 1000000)
	{
		nsec = (start.tv_usec - end.tv_usec) / 1000000;
		end.tv_usec += 1000000 * nsec;
		end.tv_sec -= nsec;
	}
	elapsed->tv_sec = start.tv_sec - end.tv_sec;
	elapsed->tv_usec = start.tv_usec - end.tv_usec;
	return (start.tv_sec < end.tv_sec);
}

void
	print_elapsed_time(
t_imestamp start,
t_imestamp end
)
{
	t_imestamp	elapsed;

	elapsed_time(start, end, &elapsed);
	printf("%ld.%.3ld\n", elapsed.tv_sec, elapsed.tv_usec / 1000);
}
