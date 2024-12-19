/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   init.c                                              :+:    :+:           */
/*                                                      +:+                   */
/*   By: mde-beer <mde-beer@student.codam.nl>          +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/12/19 14:56:41 by mde-beer       #+#    #+#                */
/*   Updated: 2024/12/19 18:29:39 by mde-beer       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void
	clean_table(
t_lock **utensils
)
{
	t_lock	*forks;

	forks = *utensils;
	while (forks && *forks)
		pthread_mutex_destroy(forks++);
	ph_free(utensils);
}

int	
	set_table(
int guestlist,
t_lock **utensils
)
{
	t_lock *const	forks = ph_calloc(guestlist, sizeof(t_lock));
	int				i;

	*utensils = forks;
	if (!forks)
		return (1);
	i = -1;
	while (++i < guestlist)
		if (pthread_mutex_init(&forks[i], NULL))
			break ;
	if (i != guestlist)
		return (clean_table(utensils), 1);
	return (0);
}

int	
	seat_guests(
int guestlist,
t_fellow **guests
)
{
	t_fellow *const	existentialists = ph_calloc(guestlist, sizeof(t_fellow));
	int				i;

	*guests = existentialists;
	if (!existentialists)
		return (1);
	i = -1;
	while (++i < guestlist)
	{
		existentialists[i].id = i;
		christen(&existentialists[i], clock());
	}
	return (0);
}
