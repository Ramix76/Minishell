/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 11:31:44 by framos-p          #+#    #+#             */
/*   Updated: 2023/06/01 16:33:28 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	getchar_custom()
{
	char	c;

	read(STDIN_FILENO, &c, 1);
	return c;
}

int	ft_prompt(t_cmd *cmd)
{
	while (1)
	{
		cmd->command = readline("MiniYo$> ");
		if (strcmp(cmd->command, "pwd") == 0)
			ft_pwd(cmd->command);
		else if (strcmp(cmd->command, "echo") == 0)
			ft_echo(cmd->command);
		else if (strcmp(cmd->command, "exit") == 0)
			break;
		add_history(cmd->command);
		free(cmd->command);
	}
	return (0);
}

int main(int argc, char **argv)
{
	t_cmd	*cmd;
	(void)argc;
	(void)argv;
	(void) ft_strlen;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (1);
	ft_prompt(cmd);
	return (0);
}
