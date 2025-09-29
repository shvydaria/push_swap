/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dashvydk <dashvydk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 15:13:02 by dashvydk          #+#    #+#             */
/*   Updated: 2025/09/25 15:16:48 by dashvydk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	get_min_index_pos(t_stack *stack)
{
	int		min_pos;
	int		min_index;
	int		i;
	t_stack	*current;

	min_pos = 0;
	min_index = stack->index;
	i = 0;
	current = stack;
	while (current)
	{
		if (current->index < min_index)
		{
			min_index = current->index;
			min_pos = i;
		}
		current = current->next;
		i++;
	}
	return (min_pos);
}

int	get_highest_index_pos(t_stack *stack)
{
	int		highest_index;
	int		pos;
	int		i;
	t_stack	*current;

	if (!stack)
		return (-1);
	highest_index = -1;
	pos = 0;
	i = 0;
	current = stack;
	while (current)
	{
		if (current->index > highest_index)
		{
			highest_index = current->index;
			pos = i;
		}
		current = current->next;
		i++;
	}
	return (pos);
}
