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
	if (s_cmd[0][0] != '.' && s_cmd[0][0] != '/')
		path = get_path(s_cmd[0], env);
	else
	{
		if (access(cmd, 0) == 0)
			path = s_cmd[0];
	}
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
	limitador = ft_strjoin(data->limiter, "\n");
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

/*void	here_doc_put_in(t_pipes *data, int *p_fd)
{
	char	*ret;
	char	*limitador;

	close(p_fd[0]);
	limitador = ft_strjoin(data->limiter, "\n");
	while (1)
	{
		ret = get_next_line(0);
		if (ft_strncmp(ret, limitador, ft_strlen(limitador)) == 0)
		{
			free(ret);
			free(limitador);
			close(p_fd[1]);
			exit(0);
		}
		ft_putstr_fd(ret, p_fd[1]);
		free(ret);
	}
}*/
/*void	here_doc(t_pipes *data)
{
	pid_t	pid;
	int		p_fd[2];

	if (pipe(p_fd) == -1)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (!pid)
	{
		close_files(data->list);
		close_pipes(data, 0);
		here_doc_put_in(data, p_fd);
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
		pipes_redirs(data, i, tmp);
		if (i == 0 || i == data->num_cmds - 1)
			redir_files(data, data->list, i);
		close_files(tmp);
		exec(data->list->docs->cmd, env);
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_pipes	*data;

	if (ac < 5)
		exit_handler(EXIT_FAILURE);
	data = ft_calloc(1, sizeof(t_pipes));
	check_args(data, av, ac);
	if (init_pid(&data) || init_list(data))
		return (1);
	if (get_cmd(data, av, 1))
	{
		ft_free_struct(data);
		return (1);
	}
	init_files(data);
	if ((ft_strncmp(av[1], "here_doc", ft_strlen(av[1])) == 0) && ac <= 5)
		ft_free_struct(data);
	parent_process(data, 0, env);
	/*else if ((ft_strncmp(av[1], "here_doc", ft_strlen(av[1])) == 0) && ac > 5)
		here_doc(&data);
	else
		first_pipe(&data, av);
	while (i < ac - 2)
		do_pipe(&data, env);
	do_pipe2(av[ac - 2], env, fd_out, p_fd);*/
}
