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
	if (execve(path, s_cmd, env) == -1)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putendl_fd(s_cmd[0], 2);
		ft_free_tab(s_cmd);
		exit(EXIT_FAILURE);
	}
}

void	child(char **av, int *p_fd, char **env)
{
	int	fd;

	close(p_fd[0]);
	fd = open_file(av[1], 0);
	dup2(fd, 0);
	close(fd);
	dup2(p_fd[1], 1);
	close(p_fd[1]);
	exec(av[2], env);
}

void	parent(char **av, int *p_fd, char **env)
{
	int	fd;

	close(p_fd[1]);
	fd = open_file(av[4], 1);
	dup2(fd, 1);
	close(fd);
	dup2(p_fd[0], 0);
	close(p_fd[0]);
	exec(av[3], env);
}

int	main(int ac, char **av, char **env)
{
	int		p_fd[2];
	pid_t	pid;
	pid_t	pid_two;

	if (ac != 5)
		exit_handler(1);
	if (pipe(p_fd) == -1)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (!pid)
		child(av, p_fd, env);
	else
	{
		pid_two = fork();
		close(p_fd[1]);
		if (!pid_two)
			parent(av, p_fd, env);
		else
		{
			close(p_fd[0]);
			waitpid(pid, 0, 0);
			waitpid(pid_two, 0, 0);
		}
	}
	return (0);
}
