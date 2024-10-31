/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavicent <pavicent@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 13:47:10 by pavicent          #+#    #+#             */
/*   Updated: 2024/10/25 13:47:12 by pavicent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_free_struct(t_pipes *data)
{
	int	i;

	i = 0;
	if (data->fd)
	{
		while (data->fd[i])
		{
			free(data->fd[i]);
			i++;
		}
		free(data->fd);
	}
	i = 0;
	if (data->pids)
		free(data->pids);
	free_fd(data);
	if (data->list)
		free_lists(data->list);
	free(data);
}

void	close_pipes(t_pipes *data, int i)
{
	while (i < data->num_cmds - 1)
	{
		if (data->fd[i])
		{
			close(data->fd[i][0]);
			close(data->fd[i][1]);
			free(data->fd[i]);
		}
		i++;
	}
	if (data->fd)
	{
		while (data->fd[i])
		{
			free(data->fd[i]);
			i++;
		}
		free(data->fd);
	}
	data->fd = NULL;
}

void	ft_free_tab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_lists(t_lists *lst)
{
	t_lists	*tmp;

	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		if (tmp->docs)
		{
			if (tmp->docs->file)
				free(tmp->docs->file);
			free(tmp->docs);
		}
		free(tmp);
	}
}

void	close_files(t_lists *list)
{
	t_lists	*tmp;

	tmp = list;
	while (list)
	{
		if (list->docs->flag > 0 && list->docs->flag != 100)
		{
			//ft_printf("%d\n", list->docs->flag);
			ft_printf("%d\n", list->docs->fd);
			close(list->docs->fd);
			//list->docs->fd = -1;
		}
		list = list->next;
	}
	list = tmp;
}
