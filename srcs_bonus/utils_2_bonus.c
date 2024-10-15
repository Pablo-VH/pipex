/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavicent <pavicent@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 13:41:03 by pavicent          #+#    #+#             */
/*   Updated: 2024/10/15 13:41:05 by pavicent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	do_pipe2(char *cmd, char **env, int fd, int *p_fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (!pid)
	{
		close(p_fd[1]);
		dup2(fd, 1);
		close(fd);
		dup2(p_fd[0], 0);
		close(p_fd[0]);
		exec(cmd, env);
	}
	else
	{
		close(p_fd[0]);
		close(p_fd[1]);
		close(fd);
		while (waitpid(-1, NULL, 0) != -1)
			continue ;
	}
}

void	check_fd_in(int fd_in)
{
		if (fd_in > 0)
		{
			dup2(fd_in, 0);
			close(fd_in);
		}
}
