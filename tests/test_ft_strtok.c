/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_strtok.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 15:41:07 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/06/19 16:40:57 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "test.utils.h"

static char* ft_strtok(char *str, const char *delim)
{
	static char	*s;
	char	*token;

	if (str == NULL)
		s = str;
	(void) delim;
	while (s != NULL && *s != '\0')
	{
		s++;
	}
	token = s;
	return (token);
}

int	main(int argc, char **argv, char **envp)
{
	const char	*delim = ft_strdup("<");
	char	*line;
	char	*t;

	init_log(argc, argv, envp);
	line = ft_strdup("<README.md <infile");
	t = strpbrk(line, delim);
	while (t != NULL)
	{
		ft_printf("%s\n", t);
		t = strpbrk(t + 1, delim);
	}
	return (0);
	(void) ft_strtok;
}
