/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   philo.h                                           :+:    :+:             */
/*                                                    +:+                     */
/*   By: mde-beer <mde-beer@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/01/04 03:53:54 by mde-beer     #+#    #+#                  */
/*   Updated: 2025/01/04 04:38:30 by mde-beer     ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdbool.h>	// required for prototype
# include <semaphore.h>	// reuqired for prototype

# define USAGE "count die eat sleep [done]" // TODO less boring
# define SEM_FORK "/forks"
# define SEM_TALK "/talking_stick"
# define MAX_PHILO 200
# define TIMEOUT 10000
# define INTERVAL 100
# define RADIX "0123456789"
# define BASE 10

typedef struct s_config	t_config;

struct s_config
{
	unsigned int	count;
	unsigned int	die;
	unsigned int	eat;
	unsigned int	eep;
	unsigned int	done;
};

size_t
	get_time(void);	// FILE: stately_affairs.c
void
	putstate(
		const char *format,
		int arg,
		size_t start
		);	// FILE: stately_affairs.c
void
	unlink_semaphores(void);	// FILE: stately_affairs.c
bool
	link_semaphores(
		int fork_count
		);	// FILE: planning.c
bool
	set_config(
		int argc,
		char **argv,
		t_config *config
		);	// FILE: planning.c
void
	philosopher(
		int id,
		size_t start,
		t_config config
		);	// FILE: philo.c
bool
	mitosis(
		t_config config
		);	// FIlE: philo.c
bool
	think(
		int id,
		size_t start,
		t_config config
		);	// FILE: verb.c
bool
	grab(
		sem_t *forks,
		int id,
		size_t start,
		t_config config
		);	// FILE: verb.c
bool
	eat(
		sem_t *forks,
		int id,
		size_t start,
		t_config config
	   );	// FILE: verb.c
bool
	stop(void);	// FILE: verb.c
int	
	error(
		const char *err,
		const int code
		);	// FILE: error.c
int	
	usage(
		const char *bin,
		const char *err
		);	// FILE: error.c
#endif
