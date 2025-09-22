/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshvydka <dshvydka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 18:11:23 by dshvydka          #+#    #+#             */
/*   Updated: 2025/09/22 15:03:58 by dshvydka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// finds the largest number and moves it to the bottom 
// swaps the top two if they are in the wrong order 
// sorts the stack in 2 moves or less.
// max_index for a 3-element stack, indices are 0, 1, 2
static void	sort_three(t_stack **a)
{
	int	max_index;

	max_index = 2;
	if ((*a)->index == max_index)
		ra(a);
	else if ((*a)->next->index == max_index)
		rra(a);
	if ((*a)->index > (*a)->next->index)
		sa(a);
}

//  move all elements from stack b back to stack a
// repeatedly finds the number in b with the highest index, 
// rotates it to the top of b (with rb or rrb) and then pushes it to a
// does this until b is empty.
static void	push_back_to_a(t_stack **a, t_stack **b)
{
	int		size_b;
	int		max_index_pos;
	t_stack	*current_b;

	while (*b)
	{
		size_b = stack_size(*b);
		max_index_pos = 0;
		current_b = *b;
		while (current_b)
		{
			if (current_b->index == stack_size(*a) + size_b - 1)
				break ;
			max_index_pos++;
			current_b = current_b->next;
		}
		if (max_index_pos <= size_b / 2)
			while (max_index_pos-- > 0)
				rb(b);
		else
			while (max_index_pos++ < size_b)
				rrb(b);
		pa(a, b);
	}
}

// pushes elements from a to b in an organized way
// divides the numbers into chunks based on their sorted index 
// goes through stack a and pushes nums to the curr chunk over to stack b
static void	k_sort(t_stack **a, t_stack **b)
{
	int	size;
	int	pushed;
	int	i;

	size = stack_size(*a);
	pushed = 0;
	i = 0;
	while (i < size && pushed < size / 2)
	{
		if ((*a)->index <= size / 2)
		{
			pb(a, b);
			pushed++;
		}
		else
			ra(a);
		i++;
	}
	while (size - pushed > 3)
	{
		pb(a, b);
		pushed++;
	}
	sort_three(a);
	push_back_to_a(a, b);
}

// checks how many elements are in the stack
// If it's 2 or 3, it calls the simple sorting functions
// If it's more than 3, it calls the k_sort
void	sort_stack(t_stack **a, t_stack **b)
{
	int	size;

	size = stack_size(*a);
	if (size <= 1 || is_sorted(*a))
		return ;
	if (size == 2)
		sa(a);
	else if (size == 3)
		sort_three(a);
	else
		k_sort(a, b);
}
