/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   mini.c                                              :+:    :+:           */
/*                                                      +:+                   */
/*   By: mde-beer <mde-beer@student.codam.nl>          +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/12/20 20:52:30 by mde-beer       #+#    #+#                */
/*   Updated: 2024/12/20 21:41:01 by mde-beer       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_PHILO 200
#define USAGE "count die eat sleep [done]"

typedef pthread_mutex_t	t_lock;

enum e_state
{
	thinking,
	eating,
	sleeping,
	dead
};

typedef struct s_philo
{
	pthread_t		thread;
	int				pid;
	t_lock			self;
	t_lock			*left;
	t_lock			*right;
	enum e_state	state;
	size_t			last_meal;
}	t_philo;

typedef struct s_program_configuration
{
	unsigned int	count;
	unsigned int	die;
	unsigned int	eat;
	unsigned int	eep;
	unsigned int	done;
}	t_config;

static t_lock	gate = PTHREAD_MUTEX_INITIALIZER;

int
	usage(
const char *bin,
const char *err
)
{
	printf("ERR: %s\n", err);
	printf("USAGE: %s %s\n", bin, USAGE);
	return (1);
}
size_t
	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void
	atomic_print_state(
const char *str,
t_philo *philo
)
{
	static t_lock	printer = PTHREAD_MUTEX_INITIALIZER;

	pthread_mutex_lock(&printer);
	pthread_mutex_lock(&philo->self);
	printf("%zu PHILO %i %s\n", get_time(), philo->pid, str);
	pthread_mutex_unlock(&philo->self);
	pthread_mutex_unlock(&printer);
}

void
	*routine(
void *arg
)
{
	t_philo *const	self = (t_philo *)arg;

	pthread_mutex_lock(&gate);
	self->last_meal = get_time();
	pthread_mutex_unlock(&gate);
	atomic_print_state("is thinking", self);
	pthread_mutex_lock(self->left);
	atomic_print_state("grabbed left", self);
	pthread_mutex_lock(self->right);
	atomic_print_state("grabbed right", self);
	atomic_print_state("is eating", self);
	usleep(1000);
	atomic_print_state("dropped both forks", self);
	pthread_mutex_unlock(self->left);
	pthread_mutex_unlock(self->right);
	atomic_print_state("goodbye", self);
	return (NULL);
}

int
	main(
int argc,
char **argv
)
{
	t_config		config;
	pthread_mutex_t	fork[MAX_PHILO];
	t_philo			philo[MAX_PHILO];
	int				i;

	if (argc < 5 || 6 < argc)
		return (usage(argv[0], "INVALID_PARAMETER_COUNT"));
	config = (t_config){.count = atoi(argv[1]),
						.die = atoi(argv[2]),
						.eat = atoi(argv[3]),
						.eep = atoi(argv[4]),
						.done = (argc == 6)?atoi(argv[5]):0 };
	i = -1;
	while (++i < config.count)
	{
		if (pthread_mutex_init(&fork[i], NULL))
			; // TODO errorhandling
		if (pthread_mutex_init(&philo[i].self, NULL))
			; // TODO errorhandling
		philo[i].pid = i;
		philo[i].left = &fork[i];
		philo[i].right = &fork[(i + 1) % config.count];
		philo[i].last_meal = SIZE_MAX;
	}
	i = -1;
	pthread_mutex_lock(&gate);
	while (++i < config.count)
		if (pthread_create(&philo[i].thread, NULL, routine, &philo[i]))
			return (printf("ERR: THREAD_CREATION\n"), 1);
	pthread_mutex_unlock(&gate);
	i = -1;
	while (++i < config.count)
		if (pthread_join(philo[i].thread, NULL))
			return (printf("ERR: THREAD_EXIT\n"), 1);
	i = -1;
	while (++i < config.count)
	{
		pthread_mutex_destroy(&fork[i]);
		pthread_mutex_destroy(&philo[i].self);
	}
}
