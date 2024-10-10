#include "pipex.h"

int	check_fd(char **av)
{
	int	fd_in;
	int	fd_out;

	fd_in = open(av[1], O_RDONLY, 0644);
	if (fd_in == -1)
	{
		if (access(av[1], F_OK) == 0)
			ft_putstr_fd("pipex: permission denied : ", 2);
		else
			ft_putstr_fd("pipex: no such file or directory: ", 2);
		ft_putendl_fd(av[1], 2);
	}
	fd_out = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_in == -1 || fd_out == -1)
	{
		if(fd_in > 0)
			close(fd_in);
		if (fd_out > 0)
			close(fd_out);
		return (-1);
	}
	close(fd_in);
	close(fd_out);
	return (0);
}
