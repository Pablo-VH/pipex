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

char	*ft_getenv(char *name, char **env);
char	*get_path(char	*cmd, char **env);
int		open_file(char *file, int in_or_out);
void	check_fd_in(int fd_in, int *i);
void	exec(char *cmd, char **env);
void	exit_handler(int n_ex);
void	do_pipe2(char *cmd, char **env, int fd, int *p_fd);
void	ft_free_tab(char **tab);

#endif
