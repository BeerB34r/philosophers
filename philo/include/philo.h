/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   philo.h                                             :+:    :+:           */
/*                                                      +:+                   */
/*   By: mde-beer <mde-beer@student.codam.nl>          +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/12/04 15:21:06 by mde-beer       #+#    #+#                */
/*   Updated: 2024/12/19 18:10:40 by mde-beer       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
//	Defines
# define MAN "\033[4m"
# define CLR "\033[0m"
# define COUNT MAN "Fellow count" CLR
# define BELL MAN "Thanatos" CLR
# define EAT MAN "Limos" CLR
# define SLEEP MAN "Hypnos" CLR
# define REPETITION "[Aethon]"
# define USAGE COUNT " " BELL " " EAT " " SLEEP " " REPETITION

//	Includes
# include <sys/time.h> //	for the declaration of t_fellow's timestamp members
# include <pthread.h> //	for the declaration of t_party's lock members
//	Datatypes
//		Typedefs
typedef struct timeval						t_imestamp;
typedef pthread_mutex_t						t_lock;
typedef struct s_philosopher				t_fellow;
typedef struct s_party						t_party;
typedef struct s_peripheral_vision_loss		t_periphery;

//		Structs
struct s_philosopher
{
	int			id;
	const char	*nationality;
	const char	*firstname;
	const char	*lastname;
	t_imestamp	last_meal;
};

struct s_party
{
	unsigned int	guestlist;		// philo count
	unsigned int	sands_of_time;	// time to die
	unsigned int	slipperiness;	// time to eat
	unsigned int	heftiness;		// time to sleep
	unsigned int	sentence_len;	// eat count, 0 == unbounded
	t_fellow		*guests;
	t_lock			*utensils;
};

struct s_peripheral_vision_loss
{
	t_fellow	myself;
	t_lock		left;
	t_lock		right;
};

//	Functions

int	
	ready(
		int argc,
		char **argv
		);	// FILE: starter_pistol.c
int	
	set(
		int argc,
		char **argv
		);	// FILE: starter_pistol.c
int	
	go(void);	// FILE: starter_pistol.c

void
	clean_table(
		t_lock **utensils
		);	// FILE: init.c
int
	set_table(
		int guestlist,
		t_lock **utensils
		);	// FILE: init.c
void
	excuse_guests(
		t_fellow **guests
		);	// FILE: init.c
int
	introduce_fellow(
		t_fellow *guest
		);	// FILE: init.c
int
	seat_guests(
		int guestlist,
		t_fellow **guests
		);	// FILE: init.c

#endif
