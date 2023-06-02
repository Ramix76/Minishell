/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 11:31:44 by framos-p          #+#    #+#             */
/*   Updated: 2023/06/02 15:48:34 by framos-p         ###   ########.fr       */
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
		cmd->command = readline("Homersh$> ");
		cmd->tokens = ft_split(cmd->command, ' ');
		if (ft_strncmp(cmd->tokens[0], "pwd", 3) == 0)
			ft_pwd(cmd->command);
		else if (ft_strncmp(cmd->tokens[0], "echo", 4) == 0)
			ft_echo(cmd);
		else if (ft_strncmp(cmd->tokens[0], "exit", 4) == 0)
			break;
		add_history(cmd->command);
		free(cmd->command);
	}
	return (EXIT_SUCCESS);
}

int main(int argc, char **argv)
{
	t_cmd	*cmd;
	(void)argc;
	(void)argv;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (1);
	ft_prompt(cmd);
	return (0);
}
