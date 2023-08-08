/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:36:48 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/08/08 18:37:33 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define START	0
#define END		1

static int	ft_getpipelines(char **tokens, int *position);
static int	ft_pipe_do(char **tokens, int start, int end, t_data *data);

int	ft_pipeline(char **tokens, t_data *data)
{
	int	i;
	int	pipeline[2];

	i = 0;
	while (tokens != NULL && tokens[i] != NULL)
	{
		pipeline[START] = i;
		ft_getpipelines(tokens, &i);
		if (ft_strcmp(tokens[i], "|") == 0)
			pipeline[END] = i - 1;
		else
			pipeline[END] = i;
		ft_pipe_do(tokens, pipeline[START], pipeline[END], data);
		++i;
	}
	return (EXIT_SUCCESS);
}

static int	ft_getpipelines(char **tokens, int *position)
{
	int	i;

	i = *position;
	while (tokens[i] != NULL && ft_strcmp(tokens[i], "|") != 0)
		++i;
	if (tokens[i] == NULL)
		--i;
	*position = i;
	return (EXIT_SUCCESS);
}

static int	ft_pipe_do(char **tokens, int start, int end, t_data *data)
{
	size_t	arr_len;
	char	**job;

	arr_len = end - start + 1;
	job = ft_arrndup(tokens + start, arr_len);
	if (job == NULL)
	{
		errno = ENOMEM;
		return (EXIT_FAILURE);
	}
	if (ft_redirections_do(job, data) == EXIT_FAILURE
		|| ft_redirections_rm(job) == EXIT_FAILURE
		|| ft_simple_command(job, data) == EXIT_FAILURE)
		return (ft_free_arr(job), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
