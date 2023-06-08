/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:01:04 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/06/08 17:07:57 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "test.utils.h"

int	pipe_do(char *line)
{
	char	**pipe_split;
	int		i;
   
	pipe_split = ft_split(line, '|');
	i = 0;
	while (pipe_split[i] != NULL)
	{
		ft_printf("%s\n", pipe_split[i]);
		++i;
	}
	return (EXIT_SUCCESS);
}

// missing strtrim

int	main(int argc, char **argv, char **envp)
{
	char	*line;

	init_log(argc, argv, envp);
	line = "cat infile | cat -n";
	pipe_do(line);
	return (0);
}
