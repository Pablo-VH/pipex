/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavicent <pavicent@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:11:34 by pavicent          #+#    #+#             */
/*   Updated: 2024/11/13 11:11:36 by pavicent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	check_args(t_pipes *data, char **av, int ac)
{
	int	i;

	if (ft_strncmp(av[1], "here_doc", ft_strlen(av[1])) == 0 && ac < 6)
	{
		free(data);
		exit_handler(2);
	}
	else if (ft_strncmp(av[1], "here_doc", ft_strlen(av[1])) == 0 && ac >= 6)
	{
		data->mode = 3;
		i = 4;
	}
	else
	{
		data->mode = 2;
		i = 3;
	}
	data->num_cmds = ac - i;
}
