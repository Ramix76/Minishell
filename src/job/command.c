/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:44:21 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/08/05 14:05:17 by mpuig-ma         ###   ########.fr       */
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
	(void) ft_command_do;
	return (EXIT_SUCCESS);
}

/*
int	ft_simple_command(char *job, t_data *data)
{
	if (ft_redirections_do(job, data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	ft_redirections_rm(job);
	ft_command_do(ft_strtrim(job, " "), data);
	return (EXIT_SUCCESS);
}
*/

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
