/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sequence_do.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:20:28 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/08/09 10:41:46 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_has_pipe(char **tokens);

int	ft_sequence_do(char **tokens, int start, int end, t_data *data)
{
	size_t	arr_len;
	char	**job;
	int		ret;

	ret = EXIT_SUCCESS;
	arr_len = end - start + 1;
	job = ft_arrndup(tokens + start, arr_len);
	if (job == NULL)
		return (errno = ENOMEM, EXIT_FAILURE);
	if (ft_has_pipe(tokens) == 0)
		ret = ft_simple_command_do(job, data);
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
