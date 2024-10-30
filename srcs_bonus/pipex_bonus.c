/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavicent <pavicent@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 13:40:51 by pavicent          #+#    #+#             */
/*   Updated: 2024/10/15 13:40:53 by pavicent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	exec(char *cmd, char **env)
{
	char	**s_cmd;
	char	*path;

	s_cmd = ft_split(cmd, ' ');
	path = get_path(s_cmd[0], env);
	if (s_cmd[0][0] != '.' && s_cmd[0][0] != '/')
		path = get_path(s_cmd[0], env);
	else
	{
		if (access(cmd, 0) == 0)
			path = s_cmd[0];
	}
	ft_printf("%s\n", path);
	if (path != NULL && access(path, X_OK) == 0)
		execve(path, s_cmd, env);
	else
	{
		perror("pipex: command not found");
		ft_free_tab(s_cmd);
		exit(EXIT_FAILURE);
	}
}

void	here_doc_put_in(t_pipes *data, int i)
{
	char	*ret;
	char	*limitador;

	close(data->fd[i][0]);
	limitador = ft_strjoin(data->list->next->docs->file, "\n");
	while (1)
	{
		ret = get_next_line(0);
		if (ft_strncmp(ret, limitador, ft_strlen(limitador)) == 0)
		{
			free(ret);
			free(limitador);
			close(data->fd[i][1]);
			exit(0);
		}
		ft_putstr_fd(ret, data->fd[i][1]);
		free(ret);
	}
}

/*void	here_doc(t_pipes *data)
{
	if (pipe(p_fd) == -1)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (!pid)
	{
		if (fd_out > 2)
			close(fd_out);
		here_doc_put_in(av, p_fd);
	}
	else
	{
		close(p_fd[1]);
		dup2(p_fd[0], 0);
		close(p_fd[0]);
		waitpid(pid, NULL, 0);
	}
}*/

int	child_process(t_pipes *data, char **env, int i, t_lists *tmp)
{
	if (do_fork(data, i))
		return (1);
	if (data->pids[i] == 0)
	{
		if (data->list->docs->flag != -1 && data->list->docs->flag != 100)
			redir_files(data, data->list, i);
		if (data->list->docs->flag == 100)
			 return (0); 
		close_files(tmp);
		pipes_redirs(data, i, tmp);
		exec(data->list->docs->file, env);
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_pipes	*data;

	if (ac < 5)
		exit_handler(EXIT_FAILURE);
	if (init_pid(&data, ac))
		return (1);
	if (init_list(data, ac))
		return (1);
	if (get_cmd(data, av))
	{
		ft_free_struct(data);
		return (1);
	}
	init_files(data);
	if ((ft_strncmp(av[1], "here_doc", ft_strlen(av[1])) == 0) && ac <= 5)
		ft_free_struct(data);
	parent_process(data, 0, ac - 1, env);
	/*else if ((ft_strncmp(av[1], "here_doc", ft_strlen(av[1])) == 0) && ac > 5)
		here_doc(&data);
	else
		first_pipe(&data, av);
	while (i < ac - 2)
		do_pipe(&data, env);
	do_pipe2(av[ac - 2], env, fd_out, p_fd);*/
}
