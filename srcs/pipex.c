/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavicent <pavicent@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:09:11 by pavicent          #+#    #+#             */
/*   Updated: 2024/10/03 12:09:13 by pavicent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec(char *cmd, char **env)
{
	char	**s_cmd;
	char	*path;

	s_cmd = ft_split(cmd, ' ');
	path = get_path(s_cmd[0], env);
	if (path != NULL && access(path, X_OK) == 0)
		execve(path, s_cmd, env);
	else
	{
		perror("pipex: command not found");
		ft_free_tab(s_cmd);
		exit(EXIT_FAILURE);
	}
}

void	child(char **av, int *p_fd, char **env, int fd_out)
{
	close(p_fd[0]);
	close(fd_out);
	dup2(p_fd[1], 1);
	close(p_fd[1]);
	exec(av[2], env);
}

void	child_two(char **av, int *p_fd, char **env, int fd_out)
{
	close(p_fd[1]);
	dup2(fd_out, 1);
	close(fd_out);
	dup2(p_fd[0], 0);
	close(p_fd[0]);
	exec(av[3], env);
}

void	parent(char **av, char **env, int *p_fd, int fd_out)
{
	pid_t	pid;
	pid_t	pid_two;

	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (!pid)
		child(av, p_fd, env, fd_out);
	else
	{
		pid_two = fork();
		if (pid_two == -1)
			exit(EXIT_FAILURE);
		close(p_fd[1]);
		if (!pid_two)
			child_two(av, p_fd, env, fd_out);
		else
		{
			close_fds(p_fd, fd_out);
			waitpid(pid, NULL, 0);
			waitpid(pid_two, NULL, 0);
		}
	}
}

int	main(int ac, char **av, char **env)
{
	int	p_fd[2];
	int	fd_in;
	int	fd_out;

	if (ac != 5)
		exit_handler(1);
	if (pipe(p_fd) == -1)
		exit(EXIT_FAILURE);
	fd_in = open_file(av[1], 0);
	if (fd_in > 0)
	{
		dup2(fd_in, 0);
		close(fd_in);
	}
	fd_out = open_file(av[4], 1);
	if (fd_in < 0)
		child_two(av, p_fd, env, fd_out);
	else
		parent(av, env, p_fd, fd_out);
	return (0);
}
