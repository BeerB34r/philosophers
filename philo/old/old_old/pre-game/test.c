/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   test.c                                              :+:    :+:           */
/*                                                      +:+                   */
/*   By: mde-beer <mde-beer@student.codam.nl>          +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/12/20 14:38:46 by mde-beer       #+#    #+#                */
/*   Updated: 2024/12/20 15:24:06 by mde-beer       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#undef COUNT
#define COUNT 20
t_lock
	*gate_holder(void)
{
	static t_lock	gate = PTHREAD_MUTEX_INITIALIZER;

	return (&gate);
}

void
	*routine(
void *arg
)
{
	const uintptr_t 	id = (uintptr_t)arg;
	static _Atomic int	num;
	static t_lock		manners = PTHREAD_MUTEX_INITIALIZER;

	pthread_mutex_lock(gate_holder());
	pthread_mutex_unlock(gate_holder());
	pthread_mutex_lock(&manners);
	printf("thread %lu reporting num as %i\n", id, num++);
	pthread_mutex_unlock(&manners);
	return (NULL);
}

int
	main(void)
{
	pthread_t	threads[COUNT];
	uintptr_t	i;

	i = -1;
	pthread_mutex_lock(gate_holder());
	printf("inviting guests...\n");
	while (++i < COUNT)
		if (pthread_create(&threads[i], NULL, routine, (void *)i))
			printf("thread %lu failed to be created\n", i);
	printf("guests seated\n");
	pthread_mutex_unlock(gate_holder());
	i = -1;
	while (++i < COUNT)
		if (pthread_join(threads[i], NULL))
			printf("Error joining thread %lu\n", i);
}
