/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshvydka <dshvydka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 18:11:23 by dshvydka          #+#    #+#             */
/*   Updated: 2025/09/24 20:17:21 by dshvydka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	get_min_index_pos(t_stack *stack)
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

static void	sort_three(t_stack **a)
{
	if (is_sorted(*a))
		return ;
	if ((*a)->index > (*a)->next->index && (*a)->index > (*a)->next->next->index)
		ra(a);
	else if ((*a)->next->index > (*a)->index
		&& (*a)->next->index > (*a)->next->next->index)
		rra(a);
	if ((*a)->index > (*a)->next->index)
		sa(a);
}

static void	sort_small(t_stack **a, t_stack **b)
{
	int	size;
	int	min_pos;

	size = stack_size(*a);
	while (size > 3)
	{
		min_pos = get_min_index_pos(*a);
		if (min_pos <= size / 2)
			while (min_pos-- > 0)
				ra(a);
		else
			while (min_pos++ < size)
				rra(a);
		pb(a, b);
		size--;
	}
	sort_three(a);
	while (*b)
		pa(a, b);
}

static int	get_highest_index_pos(t_stack *stack)
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

static void	push_back_to_a(t_stack **a, t_stack **b)
{
	int	size_b;
	int	highest_pos;

	while (*b)
	{
		size_b = stack_size(*b);
		highest_pos = get_highest_index_pos(*b);
		if (highest_pos == -1)
			break ;
		if (highest_pos <= size_b / 2)
		{
			while (highest_pos-- > 0)
				rb(b);
		}
		else
		{
			while (highest_pos++ < size_b)
				rrb(b);
		}
		pa(a, b);
	}
}


void	sort_stack(t_stack **a, t_stack **b)
{
	int	size;

	size = stack_size(*a);
	if (size == 2)
		sa(a);
	else if (size == 3)
		sort_three(a);
	else if (size <= 5)
		sort_small(a, b);
	else
	{
		int	count_b;
		int	chunk_size;

		count_b = 0;
		chunk_size = (0.000000053 * size * size) + (0.03 * size) + 14.5;
		while (stack_size(*a) > 0)
		{
			if ((*a)->index <= count_b)
			{
				pb(a, b);
				rb(b);
				count_b++;
			}
			else if ((*a)->index <= count_b + chunk_size)
			{
				pb(a, b);
				count_b++;
			}
			else
				ra(a);
		}
		push_back_to_a(a, b);
	}
}
