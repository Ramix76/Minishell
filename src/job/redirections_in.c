/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_in.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 14:27:04 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/08/05 17:53:04 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_file_in(char *filename, t_data *data);

int	ft_in(char *operator, char *value, t_data *data)
{
	if (*(operator + 1) != '\0')
	{
		if (ft_here_doc(value) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else
	{
		if (ft_file_in(value, data) == EXIT_FAILURE)
		{
			ft_fprintf(stderr, "%s: %s: %s\n", SH_NAME, value, strerror(errno));
			data->exit_code = 1;
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

static int	ft_file_in(char *filename, t_data *data)
{
	if (access(filename, R_OK) == -1)
		return (EXIT_FAILURE);
	else
	{
		if (data->in != STDIN_FILENO)
			close(data->in);
		data->in = open(filename, O_RDONLY);
		if (data->in == -1)
		{
			ft_fprintf(stderr, "%s: %s: %s\n",
				SH_NAME, filename, strerror(errno));
			data->exit_code = 1;
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}
