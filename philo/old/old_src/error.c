/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   error.c                                           :+:    :+:             */
/*                                                    +:+                     */
/*   By: mde-beer <mde-beer@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/01/02 12:03:44 by mde-beer     #+#    #+#                  */
/*   Updated: 2025/01/02 12:15:48 by mde-beer     ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

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
