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

#define MAX_STRING_LENGTH 10000

static int	ft_is_hidden_file(const char *name);
static char	*ft_allocate_and_copy_name(const char *src);
static void	ft_add_to_result(char ***result, size_t *count, const char *name);

static int	ft_is_hidden_file(const char *name)
{
	return (name[0] == '.' && ft_strcmp(name, ".") != 0
		&& ft_strcmp(name, "..") != 0);
}

static char	*ft_allocate_and_copy_name(const char *src)
{
	char	*name;
	size_t	src_len;

	src_len = ft_strlen(src);
	name = (char *)malloc(src_len + 1);
	if (name == NULL)
	{
		ft_fprintf(stderr, "Memory allocation error\n");
		return (NULL);
	}
	else
		ft_strlcpy(name, src, src_len + 1);
	return (name);
}

static void	ft_add_to_result(char ***result, size_t *count, const char *name)
{
	char	**temp;

	temp = (char **)ft_realloc(*result,
			(*count + 1) * sizeof(char *), (*count) * sizeof(char *));
	if (temp != NULL)
	{
		*result = temp;
		(*result)[*count] = ft_allocate_and_copy_name(name);
		if ((*result)[*count] != NULL)
		{
			(*count)++;
			(*result)[*count] = NULL;
		}
	}
	else
		ft_fprintf(stderr, "Memory reallocation error\n");
}

char	**ft_files_and_dirs(void)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**result;
	size_t			count;
	char			*name;

	result = NULL;
	dir = opendir(".");
	if (dir == NULL)
		return (ft_fprintf(stderr, "Error opening dir\n"), NULL);
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (!ft_is_hidden_file(entry->d_name))
		{
			name = ft_allocate_and_copy_name(entry->d_name);
			if (name != NULL)
				ft_add_to_result(&result, &count, name);
		}
		entry = readdir(dir);
	}
	closedir(dir);
	return (result);
}
