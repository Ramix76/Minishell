/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:19:38 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/08/10 16:41:39 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define WR	1
#define RD	0

static int	ft_execute(char *exec, t_cmd *cmd, t_data *data);
static int	ft_execute_fork(char *exec, t_cmd *cmd, t_data *data);

int	ft_execute_command(t_cmd *cmd, t_data *data, int fork)
{
	char	*exec;

	if (cmd->tokens[0] == NULL)
		return (EXIT_SUCCESS);
	if (cmd->tokens[0][0] != '.' && cmd->tokens[0][0] != '/')
		exec = ft_which(cmd->tokens[0], data->path);
	else
		exec = ft_realpath(cmd->tokens[0], NULL);
	if (exec == NULL)
	{
		ft_fprintf(stderr, "%s: %s: command not found\n",
			SH_NAME, cmd->tokens[0]);
		data->exit_code = 127;
		return (EXIT_FAILURE);
	}
	if (fork != 0)
		ft_execute_fork(exec, cmd, data);
	else
		ft_execute(exec, cmd, data);
	return (EXIT_SUCCESS);
}

static int	ft_execute(char *exec, t_cmd *cmd, t_data *data)
{
	ft_execvpe(exec, (char const **) cmd->tokens,
		(const char **) data->envp);
	ft_printf("%s: %s: execution error\n", SH_NAME, exec);
	return (EXIT_SUCCESS);
}

static int	ft_execute_fork(char *exec, t_cmd *cmd, t_data *data)
{
	int		fildes[2];
	pid_t	pid;
	int		savedstdout;

	if (pipe(fildes) == -1)
		return (EXIT_FAILURE);
	if (data->pipe == 0)
		savedstdout = dup(STDOUT_FILENO);
	printf("pipe: [data->fd] %d, [WR]: %d, [RD]: %d\n", data->fd, fildes[WR], fildes[RD]);
	pid = fork();
	if (pid == 0)
	{
		close(fildes[RD]);
		if (data->pipe == 1)
			dup2(fildes[WR], STDOUT_FILENO);
		close(fildes[WR]);
		ft_execvpe(exec, (char const **) cmd->tokens,
			(const char **) data->envp);
		ft_printf("%s: %s: execution error\n", SH_NAME, exec);
		exit (1);
	}
	waitpid(pid, &data->exit_code, 0);
	close(fildes[WR]);
	if (data->pipe == 1)
		dup2(fildes[RD], STDOUT_FILENO);
	else
		dup2(savedstdout, STDOUT_FILENO);
	close(fildes[RD]);
	return (EXIT_SUCCESS);
}
