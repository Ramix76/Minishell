/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 11:31:44 by framos-p          #+#    #+#             */
/*   Updated: 2023/06/05 15:14:17 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_data
{
	char	*path;
	int		exit_code;
}			t_data;

int		init_args(int argc, char **argv, char **envp, t_data *data);
int		shell_do(void);
int		command_do(char *line);

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	init_args(argc, argv, envp, &data);
	data.exit_code = shell_do();
	return (data.exit_code);
}

int	init_args(int argc, char **argv, char **envp, t_data *data)
{
	if (argc >= 2 && ft_strcmp(argv[1], "--version") == 0)
	{
		printf("%s\n", SH_VERSION);
		exit(EXIT_SUCCESS);
	}
	data->path = ft_getenv("PATH", (const char **) envp);
	data->exit_code = 0;
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
		rl_on_new_line();
		line = readline(PROMPT);
	}
	return (EXIT_SUCCESS);
}

char	*shell_expand(char *str)
{
	char	*expanded;

	expanded = str;
	return (expanded);
}

int	command_do(char *line)
{
	t_cmd	cmd;
	int		i;

	i = 0;
	cmd.command = shell_expand(line);
	cmd.tokens = ft_split(line, ' ');
	while (cmd.tokens[i] != NULL && ft_strcmp(cmd.tokens[i], ";") != 0)
	{
		//printf("- %s\n", cmd.tokens[i]);
		++i;
	}
	if (ft_strncmp(cmd.tokens[0], "pwd", 3) == 0)
		ft_pwd();
	else if (ft_strncmp(cmd.tokens[0], "echo", 4) == 0)
		ft_echo(&cmd);
	else if (ft_strncmp(cmd.tokens[0], "exit", 4) == 0)
		exit(EXIT_SUCCESS);
	else
	{
		ft_putstr_fd(SH_NAME, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(cmd.tokens[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
	}
	return (EXIT_SUCCESS);
}
