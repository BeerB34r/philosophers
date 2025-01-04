/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   utilities.c                                         :+:    :+:           */
/*                                                      +:+                   */
/*   By: mde-beer <mde-beer@student.codam.nl>          +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/12/16 14:41:23 by mde-beer       #+#    #+#                */
/*   Updated: 2024/12/16 14:54:01 by mde-beer       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>	// malloc, free
#include <string.h>	// memset
#include <stdint.h>	// numeric limits

void
	*ph_calloc(
size_t nmemb,
size_t size
)
{
	void			*out;

	if (!nmemb || !size)
		return (malloc(0));
	if (nmemb / SIZE_MAX < size)
		return (NULL);
	out = malloc(nmemb * size);
	if (!out)
		return (NULL);
	return (memset(out, 0, nmemb * size));
}

void
	ph_free(
void **memory
)
{
	if (*memory)
	{
		free(*memory);
		*memory = NULL;
	}
}
