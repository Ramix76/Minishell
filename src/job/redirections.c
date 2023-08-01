/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:40:58 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/08/01 10:50:47 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_redirections_do(char *job, t_data *data)
{
	int		i;
	char	*token;
	char	**tokens;

	i = 0;
	(void) data;
	tokens = ft_parse2tokens(job);
	while (tokens != NULL && tokens[i] != NULL)
	{
		token = tokens[i];
		if (*token == 074 || *token == 076)
		{
			printf("alert: %s\n", token);
			++i;
		}
		else
			++i;
	}
	ft_free_arr(tokens);
	return (EXIT_SUCCESS);
}

int	ft_redirections_rm(char *str)
{
	while (str != NULL && *str != '\0')
	{
		if (*str == 074 || *str == 076)
		{
			if (ft_strncmp(str, "<< ", 3) == 0
				|| ft_strncmp(str, "<< ", 3) == 0)
			{
				*str = 040;
				*(str + 1) = 040;
				*(str + 2) = 040;
				str += 3;
			}
			else
				*str++ = 040;
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
