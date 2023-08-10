/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 11:36:55 by framos-p          #+#    #+#             */
/*   Updated: 2023/08/10 14:56:47 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_str_isdigit(char *str, t_data *data);

int	ft_exit(t_cmd *cmd, t_data *data)
{
	size_t	len;

	len = ft_arrlen(cmd->tokens);
	printf("exit\n");
	if (len > 2 && ft_str_isdigit(cmd->tokens[1], data) == EXIT_SUCCESS)
	{
		ft_fprintf(stderr, "%s: exit: too many arguments\n", SH_NAME);
		return ((data->exit_code = 1), EXIT_FAILURE);
	}
	if (len > 1 && ft_str_isdigit(cmd->tokens[1], data) == EXIT_FAILURE)
	{
		ft_fprintf(stderr, "%s: exit: %s: numeric argument required\n",
			SH_NAME, cmd->tokens[1]);
		data->running = 0;
		return ((data->exit_code = 2), EXIT_FAILURE);
	}
	else if (len > 1)
		data->exit_code = ft_atoi(cmd->tokens[1]);
	data->running = 0;
	return ((data->exit_code = 0), EXIT_SUCCESS);
}

static int	ft_str_isdigit(char *str, t_data *data)
{
	while (str != NULL && *str != '\0')
	{
		if (ft_isdigit(*str) == 0)
			return ((data->exit_code = 2), EXIT_FAILURE);
		++str;
	}
	return ((data->exit_code = 0), EXIT_SUCCESS);
}
