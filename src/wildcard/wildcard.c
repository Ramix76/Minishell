/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 14:48:38 by framos-p          #+#    #+#             */
/*   Updated: 2023/07/24 16:44:27 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define MAX_STRING_LENGTH 10000

char	**ft_files_and_dirs(void)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**result;
	size_t			count;
	char			*name;

	count = 0;
	dir = opendir(".");
	if (dir != NULL)
	{
		entry = readdir(dir);
		while (entry != NULL)
		{
			if (ft_strcmp(entry->d_name, ".") != 0 
				&& ft_strcmp(entry->d_name, "..") != 0)
			{
				name = (char *)malloc(ft_strlen(entry->d_name) + 1);
				if (name == NULL)
				{
					ft_fprintf(stderr, "Memory allocation error\n");
					closedir(dir);
					ft_free_str_arr(result);
					return (NULL);
				}
				ft_strlcpy(name, entry->d_name, ft_strlen(entry->d_name) + 1);
				count++;
				result = (char **)ft_realloc(result,
						(count + 1) * sizeof(char *), count * sizeof(char *));
				if (result == NULL)
				{
					ft_fprintf(stderr, "Memory allocation error\n");
					closedir(dir);
					free(name);
					ft_free_str_arr(result);
					return (NULL);
				}
				result[count - 1] = name;
				result[count] = NULL;
			}
		}
		closedir(dir);
	}
	else 
	{
		ft_fprintf(stderr, "Error al abrir el directorio\n");
		return (NULL);
	}
	return (result);
}
