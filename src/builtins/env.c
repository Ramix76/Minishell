/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 12:12:12 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/08/10 16:11:14 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_data *data)
{
	int	i;

	i = 0;
	while (data->envp[i])
	{
		if (ft_putendl_fd(data->envp[i], STDOUT_FILENO) == -1)
		{
			return ((data->exit_code = 1), EXIT_FAILURE);
		}
		i++;
	}
	return ((data->exit_code = 0), EXIT_SUCCESS);
}
