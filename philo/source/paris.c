/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   paris.c                                             :+:    :+:           */
/*                                                      +:+                   */
/*   By: mde-beer <mde-beer@student.codam.nl>          +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/12/05 18:32:25 by mde-beer       #+#    #+#                */
/*   Updated: 2024/12/10 14:54:36 by mde-beer       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

//	takes the start time and PID of the philosopher to give them a name.
//	their name in verbose mode will then be nationality firstname PID lastname
void
	christen(
t_fellow	*fellow,
t_imestamp	seed
)
{
	const char	firstname[12][] = {"Albert", "Simone", "Fyodor", "Martin", \
							"Franz", "Søren", "Friedrich", "Viktor", "Franz", \
							"Blaise", "Henry David", "Jean-Paul" };
	const char	lastname[12][] = {"Camus", "de Beauvoir", "Dostoyevsky", \
							"Heidegger", "Kafka", "Kierkegaard", "Nietzche", \
							"Petrov", "Rosenzweig", "Pascal", "Thoreau", \
							"Sartre" };
	const char	nationality[7][] = {"French", "Russian", "German", "Danish", \
									"Bohemian", "Greek", "Swiss" };
	int			index;

	index = seed.tv_usec + fellow->id;
	fellow->firstname = firstname[index % 12];
	index = seed.tv_sec + fellow->id;
	fellow->lastname = lastname[index % 12];
	index = seed.tv_sec * seed.tv_usec + fellow_id;
	fellow->nationality = nationality[index % 7];
}
