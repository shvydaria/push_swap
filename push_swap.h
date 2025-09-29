/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dashvydk <dashvydk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:30:53 by dashvydk          #+#    #+#             */
/*   Updated: 2025/09/25 15:13:26 by dashvydk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft.h"
# include "libftprintf.h"
# include <stdlib.h>
# include <unistd.h>

typedef struct s_stack
{
	int				value;
	int				index;
	struct s_stack	*next;
	struct s_stack	*prev;
}					t_stack;

// Utils
void				ft_error(void);
int					is_numeric(const char *str);
int					is_sorted(t_stack *stack);
int					stack_size(t_stack *stack);
int					get_pos(t_stack *stack, int index);

// Memory deallocation
void				free_stack(t_stack **stack);
void				free_split(char **arr);

// Initial setup
void				init_stack(t_stack **a, char **argv);
void				assign_index(t_stack *stack);

// Sort Utils
int					get_min_index_pos(t_stack *stack);
int					get_highest_index_pos(t_stack *stack);

// Operations
void				sa(t_stack **a);
void				sb(t_stack **b);
void				ss(t_stack **a, t_stack **b);
void				pa(t_stack **a, t_stack **b);
void				pb(t_stack **a, t_stack **b);
void				ra(t_stack **a);
void				rb(t_stack **b);
void				rr(t_stack **a, t_stack **b);
void				rra(t_stack **a);
void				rrb(t_stack **b);
void				rrr(t_stack **a, t_stack **b);

// Sorting
void				sort_stack(t_stack **a, t_stack **b);

#endif
