/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstlast.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tsteur <tsteur@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/05 22:30:14 by tsteur        #+#    #+#                 */
/*   Updated: 2023/10/05 23:26:17 by tsteur        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*current_node;

	if (lst == NULL)
		return (NULL);
	current_node = lst;
	while (current_node->next != NULL)
		current_node = current_node->next;
	return (current_node);
}
