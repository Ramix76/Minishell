/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:40:58 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/08/05 15:07:23 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_mv_end(char **arr, size_t position);

int	ft_redirections_do(char **job, t_data *data)
{
	int	i;

	i = 0;
	while (job != NULL && job[i] != NULL)
	{
		if (*(job[i]) == 074)
			ft_in(job[i], job[i + 1], data);
		else if (*(job[i]) == 076)
			ft_out(job[i], job[i + 1], data);
		++i;
	}
	return (EXIT_SUCCESS);
}

int	ft_redirections_rm(char **job)
{
	int	i;

	i = ft_arrlen(job) - 1;
	while (job != NULL && job[i] != NULL)
	{
		if (*job == job[i])
			break ;
		if (*(job[i - 1]) == 074 || *(job[i - 1]) == 076)
		{
			ft_mv_end(job, i);
			ft_mv_end(job, i - 1);
		}
		--i;
	}
	return (EXIT_SUCCESS);
}

static void	ft_mv_end(char **arr, size_t position)
{
	size_t	i;
	char	*temp;

	i = position;
	while (arr != NULL && arr[i] != NULL)
	{
		if (arr[i + 1] == NULL)
			break ;
		temp = arr[i];
		arr[i] = arr[i + 1];
		arr[i + 1] = temp;
		++i;
	}
	free(arr[i]);
	arr[i] = NULL;
}
