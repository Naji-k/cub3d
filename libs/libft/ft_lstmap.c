/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstmap.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tsteur <tsteur@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/05 23:00:50 by tsteur        #+#    #+#                 */
/*   Updated: 2023/10/05 23:30:21 by tsteur        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*map;
	t_list	*current_node;
	t_list	*new_node;

	map = NULL;
	current_node = lst;
	while (current_node != NULL)
	{
		new_node = ft_lstnew(f(current_node->content));
		if (new_node == NULL)
		{
			ft_lstclear(&map, del);
			return (NULL);
		}
		ft_lstadd_back(&map, new_node);
		current_node = current_node->next;
	}
	return (map);
}
