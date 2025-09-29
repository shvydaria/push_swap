/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dashvydk <dashvydk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:31:08 by dashvydk          #+#    #+#             */
/*   Updated: 2025/09/25 15:08:17 by dashvydk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	free_stack(t_stack **stack)
{
	t_stack	*current;
	t_stack	*tmp;

	if (!stack || !*stack)
		return ;
	current = *stack;
	while (current)
	{
		tmp = current;
		current = current->next;
		free(tmp);
	}
	*stack = NULL;
}

void	free_split(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static void	parse_and_init(int argc, char **argv, t_stack **stack_a)
{
	char	**args;

	if (argc == 2)
		args = ft_split(argv[1], ' ');
	else
		args = argv + 1;
	if (!args || !*args)
	{
		if (argc == 2)
			free_split(args);
		ft_error();
	}
	init_stack(stack_a, args);
	if (argc == 2)
		free_split(args);
}

int	main(int argc, char **argv)
{
	t_stack	*stack_a;
	t_stack	*stack_b;

	if (argc < 2)
		return (0);
	stack_a = NULL;
	stack_b = NULL;
	parse_and_init(argc, argv, &stack_a);
	assign_index(stack_a);
	if (is_sorted(stack_a))
	{
		free_stack(&stack_a);
		return (0);
	}
	sort_stack(&stack_a, &stack_b);
	free_stack(&stack_a);
	return (0);
}
