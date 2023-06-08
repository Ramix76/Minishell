/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:01:04 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/06/08 18:40:34 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "test.utils.h"

int	pipe_do(char *line)
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
		ft_printf("%s\n", pipe_split[i]);
		free(pipe_split[i]);
		++i;
	}
	free(pipe_split);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;

	init_log(argc, argv, envp);
	line = "cat infile | cat -n";
	pipe_do(line);
	return (0);
}
