/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavicent <pavicent@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 12:26:34 by pavicent          #+#    #+#             */
/*   Updated: 2024/03/18 12:39:24 by pavicent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_clean_line(char *line)
{
	size_t	i;
	char	*tmp;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (line[i] == '\0' || line[1] == '\0')
		return (NULL);
	tmp = ft_substr(line, i + 1, ft_strlen(line));
	if (!*tmp)
	{
		free(tmp);
		return (NULL);
	}
	line[i + 1] = '\0';
	return (tmp);
}

char	*ft_rd_n_wr(char *buffer, int fd, char *backup)
{
	int		n_bytes;
	char	*tmp;

	n_bytes = 1;
	while (n_bytes > 0)
	{
		n_bytes = read(fd, buffer, BUFFER_SIZE);
		if (n_bytes == -1)
			return (NULL);
		else if (n_bytes == 0)
			break ;
		buffer[n_bytes] = '\0';
		if (!backup)
			backup = ft_strdup("");
		tmp = backup;
		backup = ft_strjoin(backup, buffer);
		free(tmp);
		tmp = NULL;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (backup);
}

char	*get_next_line(int fd)
{
	static char	*backup;
	char		*line;
	char		*buffer;

	buffer = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	line = ft_rd_n_wr(buffer, fd, backup);
	free(buffer);
	buffer = NULL;
	if (!line)
	{
		free(backup);
		free(line);
		line = NULL;
		backup = NULL;
		return (NULL);
	}
	backup = ft_clean_line(line);
	return (line);
}
