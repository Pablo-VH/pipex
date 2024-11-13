/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavicent <pavicent@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:24:17 by pavicent          #+#    #+#             */
/*   Updated: 2024/10/30 12:24:19 by pavicent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	free_fd(t_pipes *data)
{
	int	i;

	i = 0;
	if (data->fd)
	{
		if (data->fd[i])
		{
			while (data->fd[i])
			{
				free(data->fd[i]);
				i++;
			}
		}
		free(data->fd);
		data->fd = NULL;
	}
}

/*void	free_cmds(t_pipes *data)
{
	t_lists	*tmp;

	tmp = data->list;
	while (data->list)
	{
		if (data->list->docs->file)
			free(data->list->docs->file);
		if (data->list->docs->cmd)
	}
}*/