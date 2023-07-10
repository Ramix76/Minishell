/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_do.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 11:56:15 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/07/10 12:05:22 by mpuig-ma         ###   ########.fr       */
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
		if (ft_quotes_closed(line) == NULL)
			parsed_line = ft_expand_quotes(line);
		else
			parsed_line = line;
		printf("%s\n", parsed_line);
		exit(0);
		data->exit_code = job_control(parsed_line, data);
		//if (ft_quotes_closed(line) == NULL && parsed_line != NULL)
		//	free(parsed_line);
		free(line);
		rl_on_new_line();
		line = readline(PROMPT);
	}
	rl_clear_history();
	return (EXIT_SUCCESS);
}
