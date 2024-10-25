/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavicent <pavicent@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 13:42:09 by pavicent          #+#    #+#             */
/*   Updated: 2024/10/15 13:42:11 by pavicent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

typedef struct s_docs
{
	int		flag;
	char	*file;
	int		fd;
}			t_docs;

typedef struct s_lists
{
	t_docs			*docs;
	struct s_list	*next;
}					t_lists;

typedef struct s_pipes
{
	int		**fd;
	pid_t	*pids;
	int		num_cmds;
	char	**cmds;
	t_lists	*list;
}			t_pipes;

char	*ft_getenv(char *name, char **env);
char	*get_path(char	*cmd, char **env);
int		add_list(t_lists *list);
int		get_cmd(t_pipes *data, char **av);
int		init_fd(t_pipes *data);
int		init_list(t_pipes *data, int ac);
int		init_pid(t_pipes *data, int ac);
int		open_file(char *file, int in_or_out);
void	check_fd_in(int fd_in, int *i);
void	do_fork(t_pipes *data, int i);
void	do_pipe2(char *cmd, char **env, int fd, int *p_fd);
void	exec(char *cmd, char **env);
void	exit_handler(int n_ex);
void	ft_free_struct(t_pipes *data);
void	ft_free_tab(char **tab);
void	init_inflag(t_pipes *data, char **av, int ac);
void	init_outflags(t_lists *lst, t_lists *first);

#endif
