/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_do.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 13:29:41 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/07/31 11:31:58 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * ft_pipe_do (char *line, t_data *data)
 *
 * 		should receive a t_cmd *cmd instead of a char *line.
 *
 */

int	ft_pipe_do(char *line, t_data *data)
{
	char	**pipe_split;
	int		fd;
	int		i;

	i = 0;
	fd = STDIN_FILENO;
	pipe_split = ft_split(line, '|');
	while (pipe_split[i] != NULL)
	{
		data->exit_code = ft_execute_command(pipe_split[i++], data->envp, &fd);
	}
	close(fd);
	ft_free_str_arr(pipe_split);
	return (EXIT_SUCCESS);
}
