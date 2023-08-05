/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:19:38 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/08/05 18:24:59 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define WR	1
#define RD	0

int	ft_execute_command(t_cmd *cmd, t_data *data)
{
	char	*exec;

	printf("execute_command: %s\n", cmd->tokens[0]);
	if (cmd->tokens[0][0] != '.' && cmd->tokens[0][0] != '/')
		exec = ft_which(cmd->tokens[0], data->path);
	else
		exec = ft_realpath(cmd->tokens[0], NULL);
	if (exec == NULL)
	{
		ft_fprintf(stderr, "%s: %s: command not found\n",
			SH_NAME, cmd->tokens[0]);
		return (EXIT_FAILURE);
	}
	ft_execvpe(exec, (char const **) cmd->tokens,
		(const char **) data->envp);
	ft_printf("%s: %s: execution error\n", SH_NAME, exec);
	return (EXIT_FAILURE);
}

/*
int	ft_execute_command(t_cmd *cmd, t_data *data)
{
	char	*exec;

	//int		fildes[2];
	//pid_t	pid;
	if (cmd->tokens[0][0] != '.' && cmd->tokens[0][0] != '/')
		exec = ft_which(cmd->tokens[0], data->path);
	else
		exec = ft_realpath(cmd->tokens[0], NULL);
	if (exec == NULL)
	{
		ft_fprintf(stderr, "%s: %s: command not found\n",
			SH_NAME, cmd->tokens[0]);
		return (EXIT_FAILURE);
	}
	//if (pipe(fildes) == -1)
	//	exit(4);
	//pid = fork();
	//if (pid == -1)
	//	exit(1);
	//if (pid == 0)
	//{
	ft_execvpe(exec, (char const **) cmd->tokens,
		(const char **) data->envp);
	ft_printf("%s: %s: execution error\n", SH_NAME, exec);
	exit(EXIT_FAILURE);
	//}
	//waitpid(pid, &data->exit_code, 0);
	//if (WIFEXITED(data->exit_code))
	//	data->exit_code = WEXITSTATUS(data->exit_code);
	//close(fildes[WR]);
	return (EXIT_FAILURE);
}
*/
