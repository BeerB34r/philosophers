/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   philo.h                                             :+:    :+:           */
/*                                                      +:+                   */
/*   By: mde-beer <mde-beer@student.codam.nl>          +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/12/24 04:49:52 by mde-beer       #+#    #+#                */
/*   Updated: 2024/12/24 06:44:20 by mde-beer       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>	// typedefs and structure declaration
# include <stdbool.h>	// function prototypes

# define MAX_PHILO 200
# define USAGE "count die eat sleep [done]" // TODO less boring
# define MSG_FORK "has taken a fork\n"
# define MSG_EAT "is eating\n"
# define MSG_SLEEP "is sleeping\n"
# define MSG_THINK "is thinking\n"
# define MSG_DEAD "died\n"
# define MSG_BASE "%zu %u %s"
# define RADIX "0123456789ABCDEF"
# define BASE 10
# define INTERVAL 100

typedef pthread_mutex_t					t_lock;
typedef struct s_program_configuration	t_config;
typedef struct s_philo					t_philo;

enum e_state
{
	thinking,
	hungry,
	eating,
	sleeping,
	dead
};

struct s_program_configuration
{
	unsigned int			count;
	unsigned int			die;
	unsigned int			eat;
	unsigned int			eep;
	unsigned int			done;
	unsigned _Atomic int	*full;
	_Atomic bool			*dead;
};

struct s_philo
{
	pthread_t		thread;
	t_config		chart;
	unsigned int	pid;
	t_lock			self;
	t_lock			*left;
	t_lock			*right;
	enum e_state	state;
	size_t			start;
	size_t			last_meal;
	unsigned int	count;
};

void
	gate(
		int lock
		);	// FILE: stately_affairs.c
void
	print(
		int lock
		);	// FILE: stately_affairs.c
size_t
	get_time(void);	// FILE: stately_affairs.c
int	
	reaper(
		t_philo *const philo,
		size_t sand
		);	// FILE: stately_affairs.c
int	
	famine(
		t_philo *const philo
		);	// FILE: stately_affairs.c
bool
	set_config(
		int argc,
		char **argv,
		t_config *config
		);	// FILE: init.c
bool
	invite_guests(
		t_config config,
		t_lock fork[MAX_PHILO],
		t_philo philo[MAX_PHILO]
		);	// FILE: init.c
bool
	seat_guests(
		t_config config,
		t_philo philo[MAX_PHILO],
		pthread_t *monitor
		);	// FILE: init.c
void
	*philosopher(
		void *arg
		);	// FILE: philo.c
void
	*monitoring(
		void *arg
		);	// FILE: philo.c
void
	check_health(
		t_philo *const philo,
		t_config config
		);	// FILE: philo.c
int	
	stop(
		t_config config
		);	// FILE philo.c
int	
	state_change(
		t_philo *const philo,
		enum e_state state
		);	// FILE: philo.c
int	
	think(
		t_philo *const philo
		);	// FILE: verb.c
int	
	eat(
		t_philo *const philo
		);	// FILE: verb.c
int	
	grab(
		t_philo *const philo
		);	// FILE: verb.c
int	
	grab_first(
		t_philo *const philo
		);	// FILE: verb.c
int	
	grab_second(
		t_philo *const philo
		);	// FILE: verb.c
int	
	error(
		const char *message,
		const int code
		);	// FILE: error.c
int	
	usage(
		const char *bin,
		const char *err
		);	// FILE: error.c
void
	mutex_clean(
		int count,
		t_philo philo[MAX_PHILO]
		);	// FILE: error.c
void
	premature_death(
		int count,
		t_config config,
		t_philo philo[MAX_PHILO]
		);	// FILE: error.c
#endif
