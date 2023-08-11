/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sequence_do.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:20:28 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/08/11 13:07:11 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_has_pipe(char **tokens, int start, int end);

int	ft_sequence_do(char **tokens, int start, int end, t_data *data)
{
	size_t	arr_len;
	char	**job;
	int		ret;
	int		fd_out;

	ret = EXIT_SUCCESS;
	arr_len = end - start + 1;
	job = ft_arrndup(tokens + start, arr_len);
	if (job == NULL)
		return (errno = ENOMEM, EXIT_FAILURE);
	if (ft_strcmp(tokens[start], "(") == 0)
		ft_parenthesis_do(tokens, start + 1, end - 1, data);
	else if (ft_has_pipe(tokens, start, end) == 0)
	{
		fd_out = dup(STDOUT_FILENO);
		ret = ft_simple_command_do(job, data);
		dup2(fd_out, STDOUT_FILENO);
	}
	else
	{
		if (ft_pipeline(tokens, data) == EXIT_FAILURE)
		{
			ft_fprintf(stderr, "ft_pipeline return FAILURE\n");
			ret = EXIT_FAILURE;
		}
	}
	ft_reset_redirections(data);
	return (ft_free_arr(job), ret);
}

static int	ft_has_pipe(char **tokens, int start, int end)
{
	int	i;

	i = start;
	while (tokens[i] && i <= end)
	{
		if (ft_strcmp(tokens[i], "|") == 0)
			return (1);
		++i;
	}
	return (0);
}
