/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 10:46:20 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/08/04 13:22:12 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_quotes(char **tokens);
static int	ft_redir_in(char **tokens);
static int	ft_redir_out(char **tokens);
static int	ft_pipes(char **tokens);

int	ft_syntax_check(char **tokens)
{
	if (ft_quotes(tokens) == EXIT_FAILURE
		|| ft_redir_in(tokens) == EXIT_FAILURE
		|| ft_redir_out(tokens) == EXIT_FAILURE
		|| ft_pipes(tokens) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	ft_quotes(char **tokens)
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

static int	ft_redir_in(char **tokens)
{
	(void) tokens;
	return (EXIT_SUCCESS);
}

static int	ft_redir_out(char **tokens)
{
	(void) tokens;
	return (EXIT_SUCCESS);
}

static int	ft_pipes(char **tokens)
{
	(void) tokens;
	return (EXIT_SUCCESS);
}
