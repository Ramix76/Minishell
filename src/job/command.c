/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:44:21 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/08/05 14:26:30 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_command_do(char **job, t_data *data)
{
	int	i;

	i = 0;
	while (job[i] != NULL)
	{
		printf("job: %s\n", job[i]);
		++i;
	}
	(void) data;
	return (EXIT_SUCCESS);
}

/*
static int	ft_command_do(char *job, t_data *data)
{
	t_cmd	cmd;
	char	*exec;

	cmd.tokens = ft_split(job, ' ');
	if (cmd.tokens == NULL || cmd.tokens[0] == NULL)
		return (ft_free_str_arr(cmd.tokens), EXIT_SUCCESS);
	exec = cmd.tokens[0];
	if (ft_strcmp("exit", exec) == 0)
	{
		free(job);
		ft_free_str_arr(cmd.tokens);
		return (EXIT_SUCCESS);
	}
	else if (ft_builtin_do(&cmd, data) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	else
		ft_execute_command(&cmd, data);
	ft_free_str_arr(cmd.tokens);
	return (EXIT_SUCCESS);
}
*/
