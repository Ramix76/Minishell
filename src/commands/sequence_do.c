/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sequence_do.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:20:28 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/08/08 18:36:10 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_has_pipe(char **tokens);

int	ft_sequence_do(char **tokens, int start, int end, t_data *data)
{
	size_t	arr_len;
	char	**job;

	arr_len = end - start + 1;
	job = ft_arrndup(tokens + start, arr_len);
	if (job == NULL)
		return (errno = ENOMEM, EXIT_FAILURE);
	if (ft_has_pipe(tokens) == 0)
	{
		if (ft_redirections_do(job, data) == EXIT_FAILURE
			|| ft_redirections_rm(job) == EXIT_FAILURE
			|| ft_simple_command(job, data) == EXIT_FAILURE)
			return (ft_free_arr(job), EXIT_FAILURE);
	}
	else
	{
		if (ft_pipeline(tokens, data) == EXIT_FAILURE)
			ft_fprintf(stderr, "ft_pipeline return FAILURE\n");
	}
	ft_reset_redirections(data);
	return (ft_free_arr(job), EXIT_SUCCESS);
}

static int	ft_has_pipe(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (ft_strcmp(tokens[i], "|") == 0)
			return (1);
		++i;
	}
	return (0);
}
