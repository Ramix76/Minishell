/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_in.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 14:27:04 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/08/22 11:42:20 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_file_in(char *filename, t_data *data);

int	ft_in(char *operator, char *value, t_data *data)
{
	int	ret;

	ret = EXIT_SUCCESS;
	if (*(operator + 1) != '\0')
		ret = ft_here_doc(value, data);
	else
		ret = ft_file_in(value, data);
	dup2(data->in, STDIN_FILENO);
	close(data->in);
	return (ret);
}

static int	ft_file_in(char *filename, t_data *data)
{
	int	fd;

	if (access(filename, R_OK) == -1)
	{
		ft_fprintf(stderr, "%s: %s: %s\n",
				SH_NAME, filename, strerror(errno));
		data->exit_code = 1;
		return (EXIT_FAILURE);
	}
	else
	{
		if (isatty(data->in) == 0)
			close(data->in);
		fd = open(filename, O_RDONLY);
		if (fd == -1)
		{
			ft_fprintf(stderr, "%s: %s: %s\n",
					SH_NAME, filename, strerror(errno));
			data->exit_code = 1;
			return (EXIT_FAILURE);
		}
	}
	data->in = fd;
	return (EXIT_SUCCESS);
}
