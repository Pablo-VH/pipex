/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavicent <pavicent@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:24:31 by pavicent          #+#    #+#             */
/*   Updated: 2024/10/30 12:24:33 by pavicent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	pipes_redirs(t_pipes *data, int i, t_lists *list)
{
	if (i > 0)
	{
		if (dup2(data->fd[i - 1][0], 0) == -1)
		{
			perror("dup2 failed");
			close_pipes(data, 0);
			close_files(list);
			ft_free_struct(data);
			exit(1);
		}
	}
	if (i < data->num_cmds - 1)
	{
		if (dup2(data->fd[i][1], 1) == -1)
		{
			perror("dup2 failed");
			close_pipes(data, 0);
			close_files(list);
			ft_free_struct(data);
			exit(1);
		}
	}
	close_pipes(data, 0);
}

void	duplication(t_pipes *data, int std, t_lists *list)
{
	if (data->list->docs->fd < 0)
	{
		perror("bad fd");
		close_files(list);
		ft_free_struct(data);
		exit(1);
	}
	if (dup2(data->list->docs->fd, std) == -1)
	{
		perror("dup2 failed");
		close_files(list);
		ft_free_struct(data);
		exit(1);
	}
	close(data->list->docs->fd);
	//data->list->docs->fd = -1;
}

void	redir_files(t_pipes *data, t_lists *list, int i)
{
	if (data->list && data->list->docs && data->list->docs->file)
	{
		if (data->list->docs->flag == 2)
			duplication(data, 0, list);
		else if (data->list->docs->flag == 1)
			here_doc_put_in(data, i);
		else if (data->list->docs->flag == 4
			|| data->list->docs->flag == 3) //append
			duplication(data, 1, list);
	}
}

void	init_files(t_pipes *data)
{
	t_lists	*tmp;

	tmp = data->list;
	while (data->list)
	{
		if (data->list->docs->file &&
			ft_strncmp(data->list->docs->file,
			"here_doc", ft_strlen(data->list->docs->file)))
			open_file(data->list->docs->file, data->list->docs->flag,
				&data->list->docs->fd);
		if (data->list->docs->flag == 2)
            check_fd_in(&data->list->docs->fd);
		data->list = data->list->next;
	}
	data->list = tmp;
}

void	wait_pids(t_pipes *data, int i)
{
	while (i < data->num_cmds)
	{
		if (data->pids)
		{
			while (waitpid(data->pids[i], NULL, 0) != -1)
			continue ;
		}
		i++;
	}
}
