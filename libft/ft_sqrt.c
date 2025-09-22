/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshvydka <dshvydka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 12:56:28 by dshvydka          #+#    #+#             */
/*   Updated: 2025/09/22 12:56:30 by dshvydka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_sqrt(int nb)
{
	int	is_factor;

	if (nb < 0)
		return (0);
	is_factor = 1;
	while ((is_factor * is_factor <= nb) && is_factor <= 46340)
	{
		if ((is_factor * is_factor) == nb)
		{
			return (is_factor);
		}
		is_factor++;
	}
	if (is_factor * is_factor > nb)
	{
		return (is_factor - 1);
	}
	return (0);
}
