#include "pipex_bonus.h"

void	do_pipe2(char *cmd, char **env, int fd, int *p_fd)
{
	pid_t	pid;

	/*if (pipe(p_fd) == -1)
		exit(EXIT_FAILURE);*/
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
		waitpid(pid, NULL, 0);
	}
}
/*
int	open_file(char *file, int in_or_out)
{
	int	fd;

	if (in_or_out == 0)
	{
		fd = open(file, O_RDONLY, 0644);
		if (fd == -1)
		{
			if (access(file, F_OK) == 0)
				ft_putstr_fd("pipex: permission denied : ", 2);
			else
				ft_putstr_fd("pipex: no such file or directory: ", 2);
			ft_putendl_fd(file, 2);
		}
	}
	if (in_or_out == 1)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		exit(EXIT_FAILURE);
	return (fd);
}*/