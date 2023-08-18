/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_parenthesis.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 17:41:43 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/08/10 11:33:22 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_syntax_parenthesis(char **tokens, int i)
{
	if (ft_strcmp(tokens[i], "()") == 0 && i == 0)
	{
		return ((ft_fprintf(stderr,
					"%s: syntax error near unexpected token `)'\n",
					SH_NAME)), EXIT_FAILURE);
	}
	else if (ft_strcmp(tokens[i], "()") == 0
			&& i > 0 && ft_strchr(METACHARACTERS, *(tokens[i - 1])) != 0)
		return ((ft_fprintf(stderr,
					"%s: syntax error near unexpected token `)'\n",
					SH_NAME)), EXIT_FAILURE);
	if (*(tokens[i]) == ')'
			&& tokens[i + 1] != NULL
			&& ft_strchr("|&", *tokens[i + 1]) == NULL)
	{
		return ((ft_fprintf(stderr,
					"%s: syntax error near unexpected token here `)'\n",
					SH_NAME)), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
