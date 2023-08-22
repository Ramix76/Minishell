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

static int	ft_compute_results(char **tokens, int i, int n_parenthesis);

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

int	ft_parenthesis_closed(char **tokens)
{
	int		i;
	int		n_parenthesis;
	char	*ptr;

	i = 0;
	n_parenthesis = 0;
	while (tokens != NULL && tokens[i] != NULL && n_parenthesis >= 0)
	{
		if (ft_strchr("()", *(tokens[i])) != NULL)
		{
			ptr = tokens[i];
			while (ptr != NULL && *ptr != '\0')
			{
				if (*ptr == '(')
					++n_parenthesis;
				else if (*ptr == ')')
					--n_parenthesis;
				++ptr;
			}
		}
		++i;
	}
	return (ft_compute_results(tokens, i, n_parenthesis));
}

static int	ft_compute_results(char **tokens, int i, int n_parenthesis)
{
	--i;
	if (n_parenthesis < 0)
	{
		ft_fprintf(stderr, "%s: syntax error near unexpected token `%c'\n",
			SH_NAME, *(tokens[i]));
		return (EXIT_FAILURE);
	}
	else if (n_parenthesis > 0 && i == 0)
	{
		ft_fprintf(stderr, "%s: syntax error near unexpected end of file\n",
			SH_NAME);
		return (EXIT_FAILURE);
	}
	else if (n_parenthesis > 0)
	{
		ft_fprintf(stderr, "%s: syntax error near unexpected `newline'\n",
			SH_NAME);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
