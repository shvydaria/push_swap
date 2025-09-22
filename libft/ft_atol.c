/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshvydka <dshvydka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 13:30:00 by dashvydk          #+#    #+#             */
/*   Updated: 2025/09/22 14:10:34 by dshvydka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atol(const char *str)
{
	long	result;
	int		sign;

	result = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		if (result > (2147483647 - (*str - '0')) / 10 && sign == 1)
			return (2147483648L);
		if ((result * sign) < (-2147483648 + (*str - '0')) / 10 && sign == -1)
			return (-2147483649L);
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}
