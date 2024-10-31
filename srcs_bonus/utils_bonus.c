/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavicent <pavicent@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 13:41:14 by pavicent          #+#    #+#             */
/*   Updated: 2024/10/15 13:41:16 by pavicent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	exit_handler(int n_ex)
{
	if (n_ex == 1)
		ft_putstr_fd("./pipex infile cmd cmd outfile\n", 2);
	exit (EXIT_FAILURE);
}

void	open_file(char *file, int in_or_out, int *fd)
{
	if (in_or_out == 2)
	{
		*fd = open(file, O_RDONLY, 0644);
		ft_printf("fd = %i\n %s\n", *fd, file);
		if (*fd == -1)
		{
			if (access(file, F_OK) == 0)
				ft_putstr_fd("pipex: permission denied : ", 2);
			else
				ft_putstr_fd("pipex: no such file or directory: ", 2);
			ft_putendl_fd(file, 2);
		}
	}
	if (in_or_out == 4)
		*fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (in_or_out == 3)
		*fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
}

char	*ft_getenv(char *name, char **env)
{
	int		i;
	int		j;
	char	*sub;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		sub = ft_substr(env[i], 0, j);
		if (ft_strncmp(sub, name, ft_strlen(name)) == 0)
		{
			free(sub);
			return (env[i] + j + 1);
		}
		free(sub);
		i++;
	}
	return (NULL);
}

char	*get_path(char	*cmd, char **env)
{
	int		i;
	char	*exect;
	char	**allpath;
	char	*part_p;

	i = -1;
	if (ft_getenv("PATH", env) == NULL && access(cmd, 0) == 0)
		return (cmd);
	if (ft_getenv("PATH", env) == NULL)
		return (NULL);
	allpath = ft_split(ft_getenv("PATH", env), ':');
	while (allpath[++i])
	{
		part_p = ft_strjoin(allpath[i], "/");
		exect = ft_strjoin(part_p, cmd);
		free(part_p);
		if (access(exect, F_OK | X_OK) == 0)
		{
			ft_free_tab(allpath);
			return (exect);
		}
		free(exect);
	}
	ft_free_tab(allpath);
	return (NULL);
}

void	parent_process(t_pipes *data, int i, int ac, char **env)
{
	t_lists *tmp;

	tmp = data->list;
	while (i < ac - 1)
	{
		if (child_process(data, env, i, tmp))
			break ;
		data->list = data->list->next;
		i++;
	}
	data->list = tmp;
	close_pipes(data, 0);
	ft_printf("Padre\n");
	close_files(data->list);
	wait_pids(data, 0);
	ft_free_struct(data);
}
