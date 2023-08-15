/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 11:36:55 by framos-p          #+#    #+#             */
/*   Updated: 2023/08/15 15:05:58 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_is_numeric_argument(char *str);

int	ft_exit(t_cmd *cmd, t_data *data)
{
	size_t	len;
	int		exit_value;

	len = ft_arrlen(cmd->tokens);
	if (isatty(STDIN_FILENO))
		ft_fprintf(stderr, "exit\n");
	if (len > 2)
		return (ft_fprintf(stderr, "%s: exit: too many arguments\n",
				SH_NAME), (data->exit_code = 1), EXIT_FAILURE);
	if (len > 1)
	{
		if (!ft_is_numeric_argument(cmd->tokens[1]))
		{
			ft_fprintf(stderr, "%s: exit: %s: numeric argument required\n",
				SH_NAME, cmd->tokens[1]);
			data->running = 0;
			return ((data->exit_code = 2), EXIT_FAILURE);
		}
		exit_value = (unsigned char)ft_atoi(cmd->tokens[1]);
		if (exit_value < 1 || exit_value > 255)
			return ((data->running = 0), (data->exit_code = 2), EXIT_FAILURE);
		data->exit_code = exit_value;
	}
	data->running = 0;
	return (EXIT_SUCCESS);
}

static int	ft_is_numeric_argument(char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	if (*str == '\0')
		return (0);
	while (*str != '\0')
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}
