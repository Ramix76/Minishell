/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 11:31:44 by framos-p          #+#    #+#             */
/*   Updated: 2023/06/05 10:52:08 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_data
{
	int		exit_code;
}			t_data;

int		init_args(int argc, char **argv, char **envp, t_data *data);
int		shell_do(void);
int		command_do(char *line);
//char	getchar_custom(void);

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	init_args(argc, argv, envp, &data);
	shell_do();
	return (EXIT_SUCCESS);
}

int	init_args(int argc, char **argv, char **envp, t_data *data)
{
	(void) argc;
	(void) argv;
	(void) envp;
	(void) data;
	return (EXIT_SUCCESS);
}

int	shell_do(void)
{
	char	*line;

	line = readline(PROMPT);
	while (line != NULL)
	{
		add_history(line);
		command_do(line);
		free(line);
		line = readline(PROMPT);
	}
	return (EXIT_SUCCESS);
}

int	command_do(char *line)
{
	t_cmd	cmd;

	cmd.command = line;
	cmd.tokens = ft_split(line, ' ');
	if (ft_strncmp(cmd.tokens[0], "pwd", 3) == 0)
		ft_pwd(cmd.command);
	else if (ft_strncmp(cmd.tokens[0], "echo", 4) == 0)
		ft_echo(&cmd);
	else if (ft_strncmp(cmd.tokens[0], "exit", 4) == 0)
		exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}

/*
char	getchar_custom(void)
{
	char	c;

	read(STDIN_FILENO, &c, 1);
	return (c);
}
*/
