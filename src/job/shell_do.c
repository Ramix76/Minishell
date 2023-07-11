/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_do.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 11:56:15 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/07/11 12:34:11 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_shell_do(t_data *data)
{
	char	*line;
	char	*parsed_line;

	line = readline(PROMPT);
	while (line != NULL)
	{
		add_history(line);
		parsed_line = ft_shell_expand(line, data);
		free(line);
		data->exit_code = ft_job_control(parsed_line, data);
		free(parsed_line);
		rl_on_new_line();
		line = readline(PROMPT);
	}
	rl_clear_history();
	return (EXIT_SUCCESS);
}
