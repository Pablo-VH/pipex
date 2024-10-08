#include "pipex_bonus.h"

void	exit_handler(int n_ex)
{
	if (n_ex == 1)
		ft_putstr_fd("./pipex infile cmd cmd outfile\n", 2);
	exit (EXIT_FAILURE);
}

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
	if (in_or_out == 2)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		exit(0);
	return (fd);
}

void	ft_free_tab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
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
	allpath = ft_split(ft_getenv("PATH", env), ':');
	while (allpath[++i])
	{
		part_p = ft_strjoin(allpath[i], "/");
		exect = ft_strjoin(part_p, cmd);
		free(part_p);
		if (access(exect, F_OK | X_OK) == 0)
			return (exect);
		free(exect);
	}
	ft_free_tab(allpath);
	return (cmd);
}
