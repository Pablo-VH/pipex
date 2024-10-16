/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavicent <pavicent@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 12:37:09 by pavicent          #+#    #+#             */
/*   Updated: 2024/10/04 12:37:12 by pavicent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
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
void	close_fds(int *p_fd, int fd_out);
void	exit_handler(int n_ex);
void	ft_free_tab(char **tab);

#endif
