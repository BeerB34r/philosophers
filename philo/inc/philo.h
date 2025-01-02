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
# define RADIX "0123456789ABCDEF"
# define BASE 10
# define INTERVAL 100

typedef pthread_mutex_t					t_lock;
typedef struct s_program_configuration	t_config;
typedef struct s_philo					t_philo;

enum e_state
{
	thinking,
	eating,
	sleeping,
	dead
};

struct s_program_configuration
{
	unsigned int	count;
	unsigned int	die;
	unsigned int	eat;
	unsigned int	eep;
	unsigned int	done;
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
	size_t			last_meal;
	unsigned int	count;
};

t_lock	
	*gate(void);	// FILE: stately_affairs.c
size_t	
	get_time(void);	// FILE: stately_affairs.c
void	
	reaper(
		t_philo *const self,
		size_t sand
		);	// FILE: stately_affairs.c
void	
	set_eat(
		t_philo *const self
		);	// FILE: stately_affairs.c
void	
	set_sleep(
		t_philo *const self
		);	// FILE: stately_affairs.c
void	
	atomic_print_state(
		const char *str,
		t_philo *philo
		);	// FILE: guest.c
bool	
	die_or_print(
		t_philo *const self,
		const char *print
		);	// FILE: guest.c
void	
	grab_fork(
		t_philo *const self,
		bool odd
		);	// FILE: guest.c
void	
	eat(
		t_philo *const self
		);	// FILE: guest.c
void	
	*routine(
		void *arg
		);	// FILE: guest.c
bool	
	invite_guests(
		t_config config,
		t_lock fork[MAX_PHILO],
		t_philo philo[MAX_PHILO]
		);	// FILE: init.c
bool	
	set_config(
		int argc,
		char **argv,
		t_config *config
		);	// FILE: init.c
int		
	usage(
		const char *bin,
		const char *err
		);	// FILE: error.c
int
	error(
		const char *message,
		const int code
		);	// FILE: error.c
#endif
