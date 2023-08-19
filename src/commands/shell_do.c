/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_do.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 11:56:15 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/08/15 14:57:16 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_shell_loop(t_data *data)
{
	char	*line;

	while (data->running)
	{
		line = readline(PROMPT);
		if (line == NULL)
		{
			if (isatty(STDIN_FILENO))
				ft_fprintf(stderr, "exit\n");
			exit(data->exit_code);
		}
		if (line[0] != '\0')
			add_history(line);
		if (ft_shell_do(data, line) == EXIT_FAILURE)
			data->running = 0;
		free(line);
		rl_on_new_line();
	}
	return (rl_clear_history(), EXIT_SUCCESS);
}

int	ft_shell_do(t_data *data, char *line)
{
	char	**tokens;

	tokens = ft_parse2tokens(line);
	if (ft_syntax_check(tokens, data) != EXIT_FAILURE)
	{
		ft_shell_expand(tokens, data);
		ft_command_do(tokens, data);
	}
	ft_free_str_arr(tokens);
	return (EXIT_SUCCESS);
}
