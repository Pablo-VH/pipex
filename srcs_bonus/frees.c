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
	while (data->fd[i])
	{
		free(data->fd[i]);
		i++;
	}
	i = 0;
	if (data->pids)
		free(data->pids);
	i = 0;
	while (data->cmds[i])
	{
		free(data->cmds[i]);
		i++;
	}
	if (data->cmds)
		free(data->cmds);
	if (data->fd)
		free(data->fd);
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
		free(data->fd);
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
