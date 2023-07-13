/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 10:09:37 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/07/13 11:39:26 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_str_arr(char **split)
{
	int	i;

	if (split == NULL)
		return ;
	i = 0;
	while (split[i] != NULL)
	{
		free(split[i]);
		++i;
	}
	free(split);
}
