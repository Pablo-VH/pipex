#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include "libft.h"
# include "ft_printf.h"
# include <sys/wait.h>

char	*ft_getenv(char *name, char **env);
char	*get_path(char	*cmd, char **env);
int		open_file(char *file, int in_or_out);
void	exit_handler(int n_ex);
void	ft_free_tab(char **tab);

#endif