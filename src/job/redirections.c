/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:40:58 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/08/01 12:37:09 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define WR	1
#define RD	0

int	ft_redirections_do(char *job, t_data *data)
{
	int		i;
	char	*token;
	char	**tokens;

	i = 0;
	tokens = ft_parse2tokens(job);
	while (tokens != NULL && tokens[i] != NULL)
	{
		token = tokens[i];
		if (*token == 074 || *token == 076)
		{
			++i;
		}
		else
			++i;
	}
	ft_free_arr(tokens);
	return (EXIT_SUCCESS);
	(void) data;
}

int	ft_redirections_rm(char *str)
{
	while (str != NULL && *str != '\0')
	{
		if (*str == 074 || *str == 076)
		{
			if (ft_strncmp(str, "<< ", 3) == 0
				|| ft_strncmp(str, ">> ", 3) == 0)
				ft_memset(str, 040, 3);
			else
				ft_memset(str++, 040, 1);
			while (*str != '\0' && *str == 040)
				++str;
			while (*str != '\0' && *str != 040)
				*str++ = 040;
		}
		else
			++str;
	}
	return (EXIT_SUCCESS);
}
