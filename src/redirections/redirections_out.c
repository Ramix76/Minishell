/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_out.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 14:28:15 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/08/10 12:29:57 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_out(char *operator, char *value, t_data *data)
{
	int	fd;

	if (data->out != STDOUT_FILENO)
		close(data->out);
	if (*(operator + 1) == 076)
		fd = open(value, O_APPEND | O_WRONLY | O_CREAT, 0666);
	else
		fd = open(value, O_WRONLY | O_CREAT, 0666);
	if (fd == -1)
	{
		ft_fprintf(stderr, "%s: %s: %s\n", SH_NAME, value, strerror(errno));
		return (EXIT_FAILURE);
	}
	data->out = fd;
	dup2(data->out, STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
