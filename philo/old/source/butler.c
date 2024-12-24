/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   butler.c                                            :+:    :+:           */
/*                                                      +:+                   */
/*   By: mde-beer <mde-beer@student.codam.nl>          +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/12/19 18:30:49 by mde-beer       #+#    #+#                */
/*   Updated: 2024/12/19 18:47:26 by mde-beer       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

t_party
	*butler(
t_party *new_list
)
{
	static t_party	*party;

	if (new_list)
		party = new_list;
	return (party);
}

t_lock
	*gate(void)
{
	static t_lock	gate = PTHREAD_MUTEX_INITIALISER;

	return (&gate);
}
