/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   temporality.c                                       :+:    :+:           */
/*                                                      +:+                   */
/*   By: mde-beer <mde-beer@student.codam.nl>          +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/12/03 18:09:28 by mde-beer       #+#    #+#                */
/*   Updated: 2024/12/03 18:43:14 by mde-beer       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

struct timeval
	timestamp(
void
)
{
	struct timeval	clock;

	gettimeofday(&clock, NULL);
	return (clock);
}

int	
	elapsed_time(
struct timeval end,
struct timeval start,
struct timeval *elapsed
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
int	
	main(
void
)
{
	const struct timeval	startup = timestamp();
	struct timeval			result;

	printf("return of timestamp: %li:%li\n", startup.tv_sec, startup.tv_usec);
	if (elapsed_time(startup, timestamp(), &result))
		return (printf("elapsed time is negative\n"));
	printf("time elapsed since startup: %.1li.%.6li seconds\n", result.tv_sec, \
	result.tv_usec);
}
