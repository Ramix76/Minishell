/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 10:46:20 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/08/10 11:29:25 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define SYNERR	"syntax error"

static int	ft_quotes(char *token);
static int	ft_operators(char **tokens, int i);
static int	ft_operators_stderr(char *token, char **tokens, int i);
static int	ft_redir_out(char **tokens, int i);

int	ft_syntax_check(char **tokens, t_data *data)
{
	int	i;

	i = 0;
	while (tokens != NULL && tokens[i] != NULL)
	{
		if (ft_quotes(tokens[i]) == EXIT_FAILURE
			|| ft_operators(tokens, i) == EXIT_FAILURE
			|| ft_redir_out(tokens, i) == EXIT_FAILURE
			|| ft_syntax_parenthesis(tokens, i) == EXIT_FAILURE)
		{
			data->exit_code = 2;
			return (EXIT_FAILURE);
		}
		++i;
	}
	return (EXIT_SUCCESS);
}

static int	ft_quotes(char *token)
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

static int	ft_operators(char **tokens, int i)
{
	int		c;
	int		max_allowed;
	char	*token;

	max_allowed = 2;
	token = tokens[i];
	if (*token == 0174 || *token == 074 || *token == 076 || *token == 046
		|| *token == 050 || *token == 051)
	{
		c = *token;
		while (max_allowed-- > 0 && *token != '\0' && *token == c)
			++token;
		if (ft_operators_stderr(token, tokens, i) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	ft_operators_stderr(char *token, char **tokens, int i)
{
	if ((*(tokens[i]) == 0174 || *(tokens[i]) == 046) && i == 0)
		return (ft_fprintf(stderr, "%s: %s near unexpected token `%s'\n",
				SH_NAME, SYNERR, tokens[i]), EXIT_FAILURE);
	if (*token == '\0' && tokens[i + 1] == NULL)
		return (ft_fprintf(stderr, "%s: %s near unexpected token `newline'\n",
				SH_NAME, SYNERR), EXIT_FAILURE);
	else if (*token == '\0'
		&& ft_strchr(METACHARACTERS, *(tokens[i + 1])) != 0)
		return (ft_fprintf(stderr, "%s: %s near unexpected token `%s'\n",
				SH_NAME, SYNERR, tokens[i + 1]), EXIT_FAILURE);
	else if (*token != '\0')
		return (ft_fprintf(stderr, "%s: %s near unexpected token `%s'\n",
				SH_NAME, SYNERR, token), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	ft_redir_out(char **tokens, int i)
{
	char	*token;

	token = tokens[i];
	if (*token == 074 && *(token + 1) == 074)
	{
		if (ft_strcmp("-", tokens[i + 1]) == 0)
		{
			ft_fprintf(stderr, "%s: %s near unexpected token `newline'\n",
				SH_NAME, SYNERR);
			return (EXIT_FAILURE);
		}
		else if (*(tokens[i + 1]) == '-')
			ft_memmove(tokens[i + 1], tokens[i + 1] + 1,
				ft_strlen(tokens[i + 1]));
	}
	return (EXIT_SUCCESS);
}
