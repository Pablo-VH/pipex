#include "pipex_bonus.h"

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
		exit(0);
	}
}

void	here_doc_put_in(char **av, int *p_fd)
{
	char	*ret;

	close(p_fd[0]);
	while (1)
	{
		ret = get_next_line(0);
		if (ft_strncmp(ret, av[2], ft_strlen(av[2])) == 0)
		{
			free(ret);
			//close(p_fd[1]);
			exit(0);
		}
		ft_putstr_fd(ret, p_fd[1]);
		free(ret);
	}
}

void	here_doc(char **av, int *p_fd)
{
	pid_t	pid;

	if (pipe(p_fd) == -1)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (!pid)
		here_doc_put_in(av, p_fd);
	else
	{
		close(p_fd[1]);
		dup2(p_fd[0], 0);
		//close(p_fd[0]);
		waitpid(pid, NULL, 0);
	}
	close(p_fd[0]);
}

void	do_pipe(char *cmd, char **env, int *p_fd)
{
	pid_t	pid;

	if (pipe(p_fd) == -1)
		exit(0);
	pid = fork();
	if (pid == -1)
		exit(0);
	if (!pid)
	{
		close(p_fd[0]);
		dup2(p_fd[1], 1);
		close(p_fd[1]);
		exec(cmd, env);
	}
	else
	{
		close(p_fd[1]);
		dup2(p_fd[0], 0);
		close(p_fd[0]);
		waitpid(pid, NULL, 0);
	}
}

int	main(int ac, char **av, char **env)
{
	int		fd_in;
	int		fd_out;
	int		p_fd[2];
	int		i;

	if (ac < 5)
		exit_handler(EXIT_FAILURE);
	if (ft_strncmp(av[1], "here_doc", ft_strlen(av[1])) == 0)
	{
		if (ac < 6)
			exit_handler(EXIT_FAILURE);
		i = 3;
		here_doc(av, p_fd);
		fd_out = open_file(av[ac - 1], 2);
	}
	else
	{
		i = 2;
		fd_out = open_file(av[ac - 1], 1);
		fd_in = open_file(av[1], 0);
		dup2(fd_in, 0);
		close(fd_in);
	}
	while (i < ac - 2)
		do_pipe(av[i++], env, p_fd);
	do_pipe2(av[ac - 2], env, fd_out, p_fd);
}
