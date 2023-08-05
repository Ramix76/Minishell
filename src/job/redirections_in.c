/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_in.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 14:27:04 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/08/05 17:03:20 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_file_in(char *filename);

int	ft_in(char *operator, char *value, t_data *data)
{
	if (*(operator + 1) != '\0')
	{
		ft_here_doc(value);
	}
	else
	{
		if (ft_file_in(value) == EXIT_FAILURE)
		{
			ft_fprintf(stderr, "%s: %s: %s\n", SH_NAME, value, strerror(errno));
			data->exit_code = 1;
			return (EXIT_FAILURE);
		}
	}
	(void) data;
	return (EXIT_SUCCESS);
}

static int	ft_file_in(char *filename)
{
	if (access(filename, R_OK) == -1)
		return (EXIT_FAILURE);
	else
		printf("filename OK: %s\n", filename);
	return (EXIT_SUCCESS);
}
