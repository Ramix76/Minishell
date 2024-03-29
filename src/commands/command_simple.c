/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_simple.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:24:15 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/08/22 15:52:00 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_simple_command(t_cmd *cmd, t_data *data);
static int	ft_shell_expand_only_quotes(char **tokens, t_data *data);

int	ft_simple_command_do(char **job, t_data *data)
{
	char	*reinterpreted_line;
	int		ret;
	t_cmd	cmd;

	ret = EXIT_SUCCESS;
	data->fd_in = STDIN_FILENO;
	if (data->fd_in > -1 && isatty(data->fd_in) == 1)
		data->fd_in = dup(STDIN_FILENO);
	reinterpreted_line = ft_arr2str(job);
	cmd.tokens = ft_parse2tokens(reinterpreted_line);
	free(reinterpreted_line);
	ft_shell_expand_only_quotes(cmd.tokens, data);
	if (ft_redirections_do(cmd.tokens, data) == EXIT_FAILURE
		|| ft_redirections_rm(cmd.tokens) == EXIT_FAILURE)
		ret = EXIT_FAILURE;
	if (ft_strcmp("exit", *(cmd.tokens)) == 0)
		return (ret = ft_exit(&cmd, data), ft_free_str_arr(cmd.tokens), ret);
	if (ret != EXIT_FAILURE && ft_simple_command(&cmd, data) == EXIT_FAILURE)
		ret = EXIT_FAILURE;
	ft_free_str_arr(cmd.tokens);
	dup2(data->fd_in, STDIN_FILENO);
	close(data->fd_in);
	data->fd_in = -1;
	return (ret);
}

static int	ft_simple_command(t_cmd *cmd, t_data *data)
{
	if (ft_builtin_do(cmd, data) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	else if (data->pipe == 1)
		ft_execute_command(cmd, data, 0);
	else
		ft_execute_command(cmd, data, 1);
	return (EXIT_SUCCESS);
}

static int	ft_shell_expand_only_quotes(char **tokens, t_data *data)
{
	int		i;
	char	*token;

	i = 0;
	while (tokens != NULL && tokens[i] != NULL)
	{
		token = tokens[i];
		tokens[i] = ft_expand_quotes(tokens[i], data);
		free(token);
		++i;
	}
	return (EXIT_SUCCESS);
}
