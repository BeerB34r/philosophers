/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   atomics.c                                         :+:    :+:             */
/*                                                    +:+                     */
/*   By: mde-beer <mde-beer@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/01/03 19:53:35 by mde-beer     #+#    #+#                  */
/*   Updated: 2025/01/03 19:56:36 by mde-beer     ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void
	atomic_print(
const char *str
)
{
	static t_lock	printer = PTHREAD_MUTEX_INITIALIZER;

	pthread_mutex_lock(&printer);
	printf(str);
	pthread_mutex_unlock(&printer);
}
