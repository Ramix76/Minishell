/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:40:58 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/08/08 16:10:31 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_redirections_do(char **job, t_data *data)
{
	int	i;

	i = 0;
	while (job != NULL && job[i] != NULL)
	{
		if (*(job[i]) == 074)
		{
			if (ft_in(job[i], job[i + 1], data) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		else if (*(job[i]) == 076)
		{
			if (ft_out(job[i], job[i + 1], data) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		++i;
	}
	return (EXIT_SUCCESS);
}

int	ft_redirections_rm(char **arr)
{
	size_t	i;

	i = ft_arrlen(arr);
	while (i > 0)
	{
		if (*(arr[i - 1]) == '<' || *(arr[i - 1]) == '>')
		{
			ft_arr_rm_item(arr, i);
			ft_arr_rm_item(arr, i - 1);
		}
		--i;
	}
	return (EXIT_SUCCESS);
}

int	ft_reset_redirections(t_data *data)
{
	if (data->in != STDIN_FILENO)
		close(data->in);
	data->in = STDIN_FILENO;
	if (data->out != STDOUT_FILENO)
		close(data->out);
	data->out = STDOUT_FILENO;
	return (EXIT_SUCCESS);
}
