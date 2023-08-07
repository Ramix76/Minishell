/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 14:48:38 by framos-p          #+#    #+#             */
/*   Updated: 2023/07/26 17:16:36 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_matches_pattern(char *pattern, char *d_name);

char	*ft_expand_wildcard(char *str, t_data *data)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*temp;
	char			*expanded;

	expanded = ft_strdup(str);
	printf("str: %s\n", str);
	dir = opendir(".");
	if (dir == NULL)
		return (ft_fprintf(stderr, "%s: %s\n", SH_NAME, strerror(errno)), NULL);
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (ft_matches_pattern(str, entry->d_name) == EXIT_SUCCESS)
			printf("add: %s\n", entry->d_name);
		entry = readdir(dir);
	}
	closedir(dir);
	printf("return: %s\n", expanded);
	return (expanded);
	(void) temp;
	(void) data;
}

static int	ft_matches_pattern(char *pattern, char *d_name)
{
	printf("pattern: %s, d_name: %s\n", pattern, d_name);
	return (EXIT_SUCCESS);
}
