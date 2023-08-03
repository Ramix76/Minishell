/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_do.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 11:56:15 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/08/03 15:56:21 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_shell_do(t_data *data)
{
	char	*line;
	char	**tokens;

	while (g_running)
	{
		line = readline(PROMPT);
		if (line == NULL)
			return (printf("exit\n"), EXIT_SUCCESS);
		if (line[0] != '\0')
			add_history(line);
		tokens = ft_parse2tokens(line);
		if (ft_syntax_check(tokens) != EXIT_FAILURE)
			ft_shell_expand(tokens, data);
		free(line);
		ft_free_str_arr(tokens);
		rl_on_new_line();
	}
	rl_clear_history();
	return (EXIT_SUCCESS);
}

// when ctrl+D will need to rl_clear_history();
