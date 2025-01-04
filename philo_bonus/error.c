/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   error.c                                           :+:    :+:             */
/*                                                    +:+                     */
/*   By: mde-beer <mde-beer@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/01/04 02:39:51 by mde-beer     #+#    #+#                  */
/*   Updated: 2025/01/04 02:43:51 by mde-beer     ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
#include <stdio.h>
#include <unistd.h>

static size_t
	strlen(
const char *str
)
{
	size_t	i;

	i = -1;
	while (str[++i])
		;
	return (i);
}

int	
	error(
const char *err,
const int code
)
{
	write(2, err, strlen(err));
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
