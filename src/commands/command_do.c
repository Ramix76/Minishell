/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_do.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:44:21 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/08/09 13:27:58 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define START	0
#define END		1

static int	ft_getcommandlist(char **tokens, int *position);

/* ft_command_do() */
/* Sends tokens delimited between `()' `||' `&&' */

int	ft_command_do(char **tokens, t_data *data)
{
	int		i;
	int		sequence[2];
	bool	parenthesis;

	i = 0;
	parenthesis = 0;
	while (tokens != NULL && tokens[i] != NULL)
	{
		sequence[START] = i;
		ft_getcommandlist(tokens, &i);
		if (tokens[i] == NULL)
			--i;
		if (ft_strcmp(tokens[i], "||") == 0 || ft_strcmp(tokens[i], "&&") == 0)
			sequence[END] = i - 1;
		else
			sequence[END] = i;
		ft_sequence_do(tokens, sequence[START], sequence[END], data);
		if ((data->exit_code != 0 && tokens[i] != NULL
				&& ft_strcmp(tokens[i], "&&") == 0)
			|| (data->exit_code == 0 && tokens[i] != NULL
				&& ft_strcmp(tokens[i], "||") == 0))
			return (EXIT_FAILURE);
		++i;
	}
	return (EXIT_SUCCESS);
}

static int	ft_getcommandlist(char **tokens, int *position)
{
	int		i;
	bool	parenthesis;

	i = *position;
	parenthesis = false;
	while (tokens[i] != NULL)
	{
		if (parenthesis == false && ft_strcmp(tokens[i], "(") == 0)
			parenthesis = true;
		if (parenthesis == true && ft_strcmp(tokens[i], ")") == 0)
			parenthesis = false;
		if (tokens[i] != NULL && parenthesis == false
			&& (ft_strcmp(tokens[i], "&&") == 0
				|| ft_strcmp(tokens[i], "||") == 0))
			break ;
		++i;
	}
	*position = i;
	return (EXIT_SUCCESS);
}
