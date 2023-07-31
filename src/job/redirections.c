/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:40:58 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/07/31 15:43:34 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_perform_redirections(char *job, t_data *data)
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
			printf("alert: %s\n", token);
		++i;
	}
	ft_free_arr(tokens);
	return (EXIT_SUCCESS);
}
