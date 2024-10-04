/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavicent <pavicent@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 09:58:52 by pavicent          #+#    #+#             */
/*   Updated: 2024/02/21 17:31:07 by pavicent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_node;
	void	*buffer;

	new_list = NULL;
	if (lst || f || del)
	{
		while (lst)
		{
			buffer = (f(lst->content));
			new_node = ft_lstnew(buffer);
			if (!new_node)
			{
				del(buffer);
				ft_lstclear(&new_list, del);
				return (NULL);
			}
			ft_lstadd_back(&new_list, new_node);
			lst = lst->next;
		}
	}
	else
		return (NULL);
	return (new_list);
}
