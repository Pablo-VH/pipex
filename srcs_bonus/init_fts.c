/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fts.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavicent <pavicent@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 13:46:55 by pavicent          #+#    #+#             */
/*   Updated: 2024/10/25 13:46:58 by pavicent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	get_cmd(t_pipes *data, char **av, int i)
{
	t_lists	*tmp;

	tmp = data->list;
	data->list->docs->file = ft_strdup(av[i++]);
	while (data->list)
	{
		if (i == data->num_cmds + data->mode - 1)
		{
			data->list->docs->cmd = ft_strdup(av[i]);
			i++;
			data->list->docs->file = ft_strdup(av[i]);
			break ;
		}
		if (data->mode == 3 && i == 2)
			data->limiter = ft_strdup(av[i]);
		else
			data->list->docs->cmd = ft_strdup(av[i]);
		data->list = data->list->next;
		i++;
	}
	data->list = tmp;
	return (init_inflag(data), 0);
}

void	init_inflag(t_pipes *data)
{
	t_lists	*tmp;

	tmp = data->list;
	if (ft_strncmp(data->list->docs->file, "here_doc",
			ft_strlen(data->list->docs->file)) == 0)
	{
		data->list->docs->flag = 1;
		data->list = data->list->next;
		data->list->docs->flag = 100;
		data->list = data->list->next;
	}
	else
	{
		data->list->docs->flag = 2;
		data->list = data->list->next;
	}
	while (data->list->next != NULL)
	{
		data->list->docs->flag = -1;
		data->list = data->list->next;
	}
	init_outflags(data->list, tmp);
	data->list = tmp;
}

int	init_pid(t_pipes **data)
{
	(*data)->pids = malloc(sizeof(pid_t) * ((*data)->num_cmds));
	if (!(*data)->pids)
	{
		perror("malloc pids");
		ft_free_struct(*data);
		return (1);
	}
	if (init_fd(*data))
		return (1);
	return (0);
}

int	init_fd(t_pipes *data)
{
	int	i;

	i = 0;
	data->fd = ft_calloc(data->num_cmds, sizeof(int *));
	while (i < data->num_cmds - 1)
	{
		data->fd[i] = ft_calloc(2, sizeof(int));
		if (data->fd[i] == NULL || (pipe(data->fd[i]) == -1))
		{
			perror("malloc fd or pipe");
			ft_free_struct(data);
			return (1);
		}
		i++;
	}
	return (0);
}

int	init_list(t_pipes *data)
{
	int		i;
	t_lists	*tmp;

	i = 1;
	data->list = (t_lists *)malloc(sizeof(t_lists));
	data->list->docs = (t_docs *)malloc(sizeof(t_docs));
	if (!data->list)
	{
		ft_free_struct(data);
		return (1);
	}
	data->list->next = NULL;
	data->list->docs->fd = -1;
	tmp = data->list;
	while (i < data->num_cmds)
	{
		if (add_list(data->list))
		{
			ft_free_struct(data);
			return (1);
		}
		i++;
	}
	data->list = tmp;
	return (0);
}
