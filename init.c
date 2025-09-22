/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dashvydk <dashvydk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 13:25:33 by dashvydk          #+#    #+#             */
/*   Updated: 2025/09/12 15:43:33 by dashvydk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static t_stack	*stack_new(int value)
{
	t_stack	*new_node;

	new_node = (t_stack *)malloc(sizeof(t_stack));
	if (!new_node)
		ft_error();
	new_node->value = value;
	new_node->index = 0;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

// add a new element to the end of stack
static void	stack_add_end(t_stack **stack, t_stack *new_node)
{
	t_stack	*last;

	if (!stack || !new_node)
		return ;
	if (!*stack)
	{
		*stack = new_node;
		return ;
	}
	last = *stack;
	while (last->next)
		last = last->next;
	last->next = new_node;
	new_node->prev = last;
}

static void	check_duplicates(t_stack *stack)
{
	t_stack	*curr;
	t_stack	*temp;

	curr = stack;
	while (curr)
	{
		temp = curr->next;
		while (temp)
		{
			if (curr->value == temp->value)
				ft_error();
			temp = temp->next;
		}
		curr = curr->next;
	}
}

void	init_stack(t_stack **a, char **argv)
{
	long	num;
	int		i;

	i = 0;
	while (argv[i])
	{
		if (!is_numeric(argv[i]))
			ft_error();
		num = ft_atol(argv[i]);
		if (num > 2147483647 || num < -2147483648)
			ft_error();
		stack_add_end(a, stack_new((int)num));
		i++;
	}
	check_duplicates(*a);
}

void	assign_index(t_stack *stack)
{
	t_stack	*curr;
	t_stack	*temp;
	int		index;

	curr = stack;
	while (curr)
	{
		index = 0;
		temp = stack;
		while (temp)
		{
			if (curr->value > temp->value)
				index++; // Count how many other numbers are smaller
			temp = temp->next;
		}
		curr->index = index;
		curr = curr->next;
	}
}
