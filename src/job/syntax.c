/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 10:46:20 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/08/03 16:09:35 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_syntax_check(char **tokens)
{
	int	i;

	i = 0;
	while (tokens != NULL && tokens[i] != NULL)
	{
		if (ft_quotes_closed(tokens[i]) != NULL)
		{
			ft_fprintf(stderr,
				"%s: unexpected EOF while looking for matching `%c\'\n",
				SH_NAME, *(ft_quotes_closed(tokens[i])));
			return (EXIT_FAILURE);
		}
		++i;
	}
	return (EXIT_SUCCESS);
}
