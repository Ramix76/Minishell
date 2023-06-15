/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_do.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 11:56:40 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/06/15 11:27:34 by mpuig-ma         ###   ########.fr       */
/*   Updated: 2023/06/12 15:32:22 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// parse to t_cmd
// execute comand (either builtin or not)
// all builtins should accept as arguments (t_cmd *cmd, t_data *data) ??

static int	pipe_do(char *line, t_data *data);
static int	pipex(int argc, char **argv, t_data *data);
static void	execute_command(char *argv, char **envp, int *fd);

int	command_do(char *line, t_data *data)
{
	t_cmd	cmd;
	char	*cmd_str;

	cmd.command = shell_expand(line, data);
	cmd.tokens = ft_split(line, ' ');
	if (cmd.tokens[0] == NULL)
	{
		free_str_arr(cmd.tokens);
		return (EXIT_SUCCESS);
	}
	cmd_str = ft_which(cmd.tokens[0], data->path);
	if (is_builtin(cmd.tokens[0]) == EXIT_SUCCESS)
		builtin_do(&cmd, data);
	else if (ft_strncmp(cmd.tokens[0], "exit", 4) == 0)
	{
		free(cmd_str);
		free_str_arr(cmd.tokens);
		exit (EXIT_SUCCESS);
	}
	else if (cmd_str == NULL)
		ft_fprintf(stderr, "%s: %s: command not found\n",
			SH_NAME, cmd.tokens[0]);
	else
	{
		pipe_do(cmd_str, data);
	}
	free(cmd_str);
	free_str_arr(cmd.tokens);
	return (EXIT_SUCCESS);
}

static int	pipe_do(char *line, t_data *data)
{
	char	**pipe_split;
	char	*str;
	int		i;

	pipe_split = ft_split(line, '|');
	i = 0;
	while (pipe_split[i] != NULL)
	{
		str = ft_strtrim(pipe_split[i], " ");
		free(pipe_split[i]);
		pipe_split[i] = str;
		++i;
	}
	pipex(i, pipe_split, data);
	i = 0;
	while (pipe_split[i] != NULL)
		free(pipe_split[i++]);
	free(pipe_split);
	return (EXIT_SUCCESS);
}

static int	pipex(int argc, char **argv, t_data *data)
{
	int	i;
	int	fd;

	i = 0;
	fd = STDIN_FILENO;
	while (i < argc)
	{
		//dup2(fd, STDIN_FILENO);
		//close(fd);
		execute_command(argv[i], data->envp, &fd);
		++i;
	}
	//close(fd);
	return (EXIT_SUCCESS);
}

static void	execute_command(char *argv, char **envp, int *fd)
{
	int		fildes[2];
	char	**cmd;
	pid_t	pid;

	if (pipe(fildes) == -1)
		exit (4);
	pid = fork();
	if (pid == -1)
	{
		perror("pipex");
		exit(1);
	}
	if (pid == 0)
	{
		cmd = ft_split(argv, ' ');
		//dup2(fildes[WR], STDOUT_FILENO);
		//close(fildes[RD]);
		//close(fildes[WR]);
		ft_execvpe(cmd[0], (char const **) cmd, (const char **) envp);
		exit (1);
	}
	waitpid(pid, NULL, 0);
	//close(fildes[WR]);
	//*fd = fildes[RD];
	(void) fd;
}
