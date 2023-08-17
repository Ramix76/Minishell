/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:19:38 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/08/17 14:06:52 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_execute_cmd(char *exec, t_cmd *cmd, t_data *data, int fork);

int	ft_execute_command(t_cmd *cmd, t_data *data, int fork)
{
	char	*exec;

	if (cmd->tokens[0] == NULL)
		return (EXIT_SUCCESS);
	if (cmd->tokens[0][0] != '.' && cmd->tokens[0][0] != '/')
		exec = ft_which(cmd->tokens[0],
				ft_getenv("PATH", (const char **) data->envp));
	else
		exec = ft_realpath(cmd->tokens[0], NULL);
	if (exec == NULL && ft_getenv("PATH", (const char **) data->envp) != NULL)
	{
		ft_fprintf(stderr, "%s: %s: command not found\n",
			SH_NAME, cmd->tokens[0]);
		return ((data->exit_code = 127), EXIT_FAILURE);
	}
	else if (exec == NULL
		&& ft_getenv("PATH", (const char **) data->envp) == NULL)
	{
		exec = ft_realpath(cmd->tokens[0], NULL);
		if (exec == NULL)
			return ((data->exit_code = 127),
				(ft_fprintf(stderr, "%s: %s: No such file or directory\n",
						SH_NAME, cmd->tokens[0])), EXIT_FAILURE);
	}
	return ((ft_execute_cmd(exec, cmd, data, fork)), EXIT_SUCCESS);
}

static void	ft_execute_cmd(char *exec, t_cmd *cmd, t_data *data, int frk)
{
	pid_t	pid;
	int		status;

	if (frk == 0)
		ft_execvpe(exec, (char const **) cmd->tokens,
			(const char **) data->envp);
	else
	{
		pid = fork();
		if (pid == 0)
		{
			ft_execvpe(exec, (char const **) cmd->tokens,
				(const char **) data->envp);
		}
		else
		{
			waitpid(pid, &status, 0);
			if (WIFEXITED(status))
				data->exit_code = WEXITSTATUS(status);
		}
	}
}
