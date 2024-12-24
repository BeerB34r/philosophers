/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   threxperimentation.c                                :+:    :+:           */
/*                                                      +:+                   */
/*   By: mde-beer <mde-beer@student.codam.nl>          +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/12/16 14:38:22 by mde-beer       #+#    #+#                */
/*   Updated: 2024/12/16 18:45:51 by mde-beer       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>	// pthread suite
#include <stdio.h>		// printf
#include <stdbool.h>	// boolean type
#include <unistd.h>		// usleep
#include <stdint.h>		// uintptr_t
#include <philo.h>		// various datatypes
#define MAX_THREADS 200
#define GRAB false
#define SLIP true

t_imestamp	timestamp(void);
int	print_elapsed_time(t_imestamp start, t_imestamp end);
t_imestamp g_startup;

bool
	touch_sporks(
int id,
bool action
)
{
	static pthread_mutex_t	lock = PTHREAD_MUTEX_INITIALIZER;
	static bool				sporks[MAX_THREADS];
	bool					status;

	pthread_mutex_lock(&lock);
	status = (sporks[id] | sporks[(id + 1) % MAX_THREADS]);
	if (action)
	{
		sporks[id] = false;
		sporks[(id + 1) % MAX_THREADS] = false;
	}
	else if (!status)
	{
		sporks[id] = true;
		sporks[(id + 1) % MAX_THREADS] = true;
	}
	pthread_mutex_unlock(&lock);
	return (status);
}

void
	*thread_func(
void *arg
)
{
	const uintptr_t	id = (uintptr_t)arg;

	while (touch_sporks(id, GRAB))
		usleep(100);
	print_elapsed_time(g_startup, timestamp());
	printf("i, %lu, touched the sporks, eeping now!\n", id);
	usleep(1000);
	print_elapsed_time(g_startup, timestamp());
	printf("i, %lu, am finished eeping, killing myself now!\n", id);
	touch_sporks(id, SLIP); 
	return (NULL);
}

int
	main(
int argc,
char **argv
)
{
	pthread_t	threads[MAX_THREADS];
	uintptr_t	i;

	g_startup = timestamp();
	i = -1;
	while (++i < MAX_THREADS)
	{
		if (pthread_create(&threads[i], NULL, thread_func, (void *)i))
			printf("thread %lu failed to be created\n", i);
	}
	i = -1;
	while (++i < MAX_THREADS)
		if (pthread_join(threads[i], NULL))
			printf("Error joining thread %lu\n", i);
}
