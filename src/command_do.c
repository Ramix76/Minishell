/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_do.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 11:56:40 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/06/08 11:51:48 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// parse to t_cmd
// execute comand (either builtin or not)
// all builtins should accept as arguments (t_cmd *cmd, t_data *data) ??

int	command_do(char *line, t_data *data)
{
	t_cmd	cmd;
	int		i;
	char	*cmd_str;

	i = 0;
	cmd.command = shell_expand(line);
	cmd.tokens = ft_split(line, ' ');
	cmd_str = ft_which(cmd.tokens[0], data->path);
	if (is_builtin(cmd.tokens[0]) == EXIT_SUCCESS)
		builtin_do(&cmd, data);
	//else if (ft_strncmp(cmd.tokens[0], "exit", 4) == 0)
	//{
	//	free(cmd_str);
	//	free_str_arr(cmd.tokens);
	//	return (EXIT_SUCCESS);
	//}
	else if (cmd_str == NULL)
		ft_fprintf(stderr, "%s: %s: command not found\n",
			SH_NAME, cmd.tokens[0]);
	else
		ft_printf("Should execute %s\n", cmd_str);
	free(cmd_str);
	free_str_arr(cmd.tokens);
	return (EXIT_SUCCESS);
}
