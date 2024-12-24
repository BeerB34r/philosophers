/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   mini.c                                              :+:    :+:           */
/*                                                      +:+                   */
/*   By: mde-beer <mde-beer@student.codam.nl>          +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/12/20 20:52:30 by mde-beer       #+#    #+#                */
/*   Updated: 2024/12/24 06:43:20 by mde-beer       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#define MAX_PHILO 200
#define USAGE "count die eat sleep [done]"
#define INTERVAL 100

typedef pthread_mutex_t	t_lock;

enum e_state
{
	thinking,
	eating,
	sleeping,
	dead
};

typedef struct s_program_configuration
{
	unsigned int	count;
	unsigned int	die;
	unsigned int	eat;
	unsigned int	eep;
	unsigned int	done;
}	t_config;

typedef struct s_philo
{
	pthread_t		thread;
	unsigned int	pid;
	t_lock			self;
	t_lock			*left;
	t_lock			*right;
	enum e_state	state;
	size_t			last_meal;
	unsigned int	count;
	t_config		chart;
}	t_philo;

static t_lock	gate = PTHREAD_MUTEX_INITIALIZER;

bool died(t_philo *const self);

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
	static size_t	start;
	static t_lock	printer = PTHREAD_MUTEX_INITIALIZER;

	pthread_mutex_lock(&printer);
	if (!start)
		start = get_time();
	pthread_mutex_lock(&philo->self);
	printf("%zu %i %s\n", get_time() - start, philo->pid, str);
	pthread_mutex_unlock(&philo->self);
	pthread_mutex_unlock(&printer);
}

bool
	die_or_print(
t_philo *const self,
const char *print
)
{
	static t_lock	deadlock = PTHREAD_MUTEX_INITIALIZER;
	static bool		finished = false;

	pthread_mutex_lock(&deadlock);
	if (finished)
		return (pthread_mutex_unlock(&deadlock), true);
	pthread_mutex_lock(&self->self);
	if (self->state == dead || self->last_meal < get_time() - self->chart.die)
	{
		finished = true;
		pthread_mutex_unlock(&self->self);
		atomic_print_state("has died", self);
		pthread_mutex_unlock(&deadlock);
		return (true);
	}
	pthread_mutex_unlock(&self->self);
	if (print)
		atomic_print_state(print, self);
	pthread_mutex_unlock(&deadlock);
	return (false);
}

void
	reaper(
t_philo *const self,
size_t sand
)
{
	while (sand > get_time())
	{
		if (die_or_print(self, NULL))
			return ;
		usleep(INTERVAL);
	}
}

void
	grab_fork(
t_philo *const self,
bool odd
)
{
	if (odd)
		pthread_mutex_lock(self->left);
	else
		pthread_mutex_lock(self->right);
	if (die_or_print(self, NULL))
	{
		pthread_mutex_unlock(self->left);
		pthread_mutex_unlock(self->right);
		return ;
	}
	die_or_print(self, "has taken a fork");
}

void
	set_eat(
t_philo *const self
)
{
	pthread_mutex_lock(&self->self);
	self->last_meal = get_time();
	self->state = eating;
	self->count++;
	pthread_mutex_unlock(&self->self);
	die_or_print(self, "is eating");
}

void
	set_sleep(
t_philo *const self
)
{
	pthread_mutex_lock(&self->self);
	self->state = sleeping;
	pthread_mutex_unlock(&self->self);
	die_or_print(self, "is sleeping");
}

void
	eat(
t_philo *const self
)
{
	if (die_or_print(self, NULL))
		return ;
	grab_fork(self, self->pid % 2);
	if (die_or_print(self, NULL))
		return ;
	if (self->left == self->right)
	{
		reaper(self, SIZE_MAX);
		pthread_mutex_unlock(self->left);
		pthread_mutex_unlock(self->right);
		return ;
	}
	grab_fork(self, !(self->pid % 2));
	if (die_or_print(self, NULL))
		return ;
	set_eat(self);
	reaper(self, self->chart.eat + get_time());
	pthread_mutex_unlock(self->left);
	pthread_mutex_unlock(self->right);
	if (die_or_print(self, NULL) || self->count == self->chart.done)
		return ;
	set_sleep(self);
	reaper(self, self->chart.eep + get_time());
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
	while (self->chart.done == 0 || self->count < self->chart.done)
	{
		if (die_or_print(self, "is thinking"))
			return (NULL);
		eat(self);
	}
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
	unsigned int	i;

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
		philo[i].pid = i + 1;
		philo[i].left = &fork[i];
		philo[i].right = &fork[(i + 1) % config.count];
		philo[i].last_meal = SIZE_MAX;
		philo[i].count = 0;
		philo[i].chart = config;
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
