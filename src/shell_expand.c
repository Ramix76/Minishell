/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:45:44 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/07/11 12:12:55 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * name: A word consisting solely of letters, numbers, and underscores, 
 * and beginning with a letter or underscore. 
 * Names are used as shell variable and function names.
 * Also referred to as an identifier.
 *
 * ft_getname(char *ptr)
 * returns name portion from string
 *
 */

char	*ft_getname(char *ptr)
{
	char	*name;
	size_t	name_len;

	if (ptr == NULL || *ptr == '\0' || *ptr != '$')
		return (NULL);
	++ptr;
	name_len = 0;
	if (*ptr == '\0' && (ft_isalpha(*ptr) == 0 || *ptr != '_'))
		return (NULL);
	while (ptr[name_len] != '\0' && (ft_isalnum(ptr[name_len]) != 0
			|| ptr[name_len] == '_'))
		++name_len;
	name = ft_strndup(ptr, name_len);
	return (name);
}

char	*shell_expand(char *line, t_data *data)
{
	char	*expanded;
	char	*dollar;
	char	*name;
	char	*value;
	char	*temp;
	size_t	name_len;
	size_t	p;

	expanded = ft_strdup(line);
	dollar = ft_strchr(expanded, '$');
	while (dollar != NULL)
	{
		name = ft_getname(dollar);
		if (name != NULL)
		{
			value = ft_getenv(name, (const char **) data->envp);
			if (value == NULL)
				value = "";
			name_len = ft_strlen(name);
			ft_memmove(dollar + 1, dollar + 1 + name_len,
				ft_strlen(dollar + name_len));
			p = ft_strchr(expanded, '$') - expanded;
			temp = ft_strpjoin_replace(expanded, value, p);
			free(expanded);
			expanded = temp;
			free(name);
		}
		dollar = ft_strchr(expanded, '$');
	}
	return (expanded);
}
