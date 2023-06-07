/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_do.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 11:56:15 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/06/07 13:27:00 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	shell_do(t_data *data)
{
	char	*line;

	line = readline(PROMPT);
	while (line != NULL)
	{
		add_history(line);
		command_do(line, data);
		free(line);
		rl_on_new_line();
		line = readline(PROMPT);
	}
	return (EXIT_SUCCESS);
}