/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:40:58 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/08/05 14:12:35 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_in(int i, char **tokens, t_data *data);
static int	ft_out(int i, char **tokens, t_data *data);

int	ft_redirections_do(char **job, t_data *data)
{
	(void) job;
	(void) data;
	return (EXIT_SUCCESS);
	(void) ft_in;
	(void) ft_out;
}

/*
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
		if (*token == 074)
		{
			ft_in(i, tokens, data);
			++i;
		}
		else if (*token == 076)
		{
			ft_out(i, tokens, data);
			++i;
		}
		else
			++i;
	}
	ft_free_arr(tokens);
	return (EXIT_SUCCESS);
	(void) data;
}
*/

static int	ft_in(int i, char **tokens, t_data *data)
{
	if (tokens[i + 1] == NULL)
		ft_fprintf(stderr, "ft_in: error\n");
	close(data->in);
	//data->in = open();
	return (EXIT_SUCCESS);
}

static int	ft_out(int i, char **tokens, t_data *data)
{
	if (tokens[i + 1] == NULL)
		ft_fprintf(stderr, "ft_out: error\n");
	close(data->out);
	(void) data;
	return (EXIT_SUCCESS);
}

int	ft_redirections_rm(char **job)
{
	(void) job;
	return (EXIT_SUCCESS);
}

/*
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
*/
