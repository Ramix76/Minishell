/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 10:46:20 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/08/04 15:14:13 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define SYNERR	"syntax error"

int	ft_syntax_check(char **tokens)
{
	int	i;

	i = 0;
	while (tokens != NULL && tokens[i] != NULL)
	{
		if (ft_quotes(tokens[i]) == EXIT_FAILURE
			|| ft_operators(tokens, i) == EXIT_FAILURE
			|| ft_redir_in(tokens[i]) == EXIT_FAILURE
			|| ft_redir_out(tokens[i]) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		++i;
	}
	return (EXIT_SUCCESS);
}

int	ft_quotes(char *token)
{
	if (ft_quotes_closed(token) != NULL)
	{
		ft_fprintf(stderr,
			"%s: unexpected EOF while looking for matching `%c\'\n",
			SH_NAME, *(ft_quotes_closed(token)));
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	ft_operators(char **tokens, int i)
{
	int		c;
	int		max_allowed;
	char	*token;

	max_allowed = 2;
	token = tokens[i];
	if (*token == 0174 || *token == 074 || *token == 076)
	{
		c = *token;
		while (max_allowed-- > 0 && *token != '\0' && *token == c)
			++token;
		if (*token == '\0' && tokens[i + 1] == NULL)
		{
			ft_fprintf(stderr, "%s: %s near unexpected token `newline'\n",
				SH_NAME, SYNERR);
			return (EXIT_FAILURE);
		}
		else if (*token != '\0')
		{
			ft_fprintf(stderr, "%s: %s near unexpected token `%s'\n",
				SH_NAME, SYNERR, token);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

int	ft_redir_in(char *token)
{
	(void) token;
	return (EXIT_SUCCESS);
}

int	ft_redir_out(char *token)
{
	(void) token;
	return (EXIT_SUCCESS);
}
