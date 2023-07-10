/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_do.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 11:56:15 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/07/10 16:50:22 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	shell_do(t_data *data)
{
	char	*line;
	char	*parsed_line;

	line = readline(PROMPT);
	while (line != NULL)
	{
		add_history(line);
		parsed_line = shell_expand(line, data);
		free(line);
		
		printf("%s\n", parsed_line);
		//data->exit_code = job_control(parsed_line, data);
		free(parsed_line);
		exit(0);
		
		rl_on_new_line();
		line = readline(PROMPT);
	}
	rl_clear_history();
	return (EXIT_SUCCESS);
}
