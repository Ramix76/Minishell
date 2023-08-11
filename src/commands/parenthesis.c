/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 13:22:16 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/08/10 13:09:37 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_parenthesis_do(char **tokens, int start, int end, t_data *data)
{
	size_t	arr_len;
	char	**job;

	printf("parenthesis: %s, %s\n", tokens[start], tokens[end]);
	arr_len = end - start + 1;
	job = ft_arrndup(tokens + start, arr_len);
	if (job == NULL)
		return (errno = ENOMEM, EXIT_FAILURE);
	ft_command_do(job, data);
	return (EXIT_SUCCESS);
}
