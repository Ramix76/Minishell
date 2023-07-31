/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:43:35 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/07/31 15:45:27 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_job_control(char *line, t_data *data)
{
	int		i;
	char	*job;
	char	**split;

	i = 0;
	split = ft_split(line, '|');
	while (split != NULL && split[i] != NULL)
	{
		job = ft_strtrim(split[i], " ");
		ft_simple_command(job, data);
		free(job);
		++i;
	}
	ft_free_arr(split);
	return (EXIT_SUCCESS);
}
