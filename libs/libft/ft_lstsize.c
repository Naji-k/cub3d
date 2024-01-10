/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstsize.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tsteur <tsteur@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/05 22:26:29 by tsteur        #+#    #+#                 */
/*   Updated: 2023/10/05 23:20:25 by tsteur        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		size;
	t_list	*current_node;

	size = 0;
	current_node = lst;
	while (current_node != NULL)
	{
		current_node = current_node->next;
		size++;
	}
	return (size);
}
