/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:45:44 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/07/10 17:29:22 by mpuig-ma         ###   ########.fr       */
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
	// beginning with a letter or underscore.
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
	char	*temp;
	char	*name;
	char	*name_value;

	dollar = ft_strchr(line, '$');
	if (dollar != NULL)
		expanded = ft_strndup(line, line - dollar);
	while (dollar != NULL)
	{
		name = ft_getname(dollar);
		if (name != NULL)
		{
			name_value = ft_getenv(name, (const char **) data->envp);
			if (name_value == NULL)
				name_value = "";
			temp = ft_strjoin("", name_value);
			free(expanded);
			expanded = temp;
		}
		if (name != NULL)
		{
			dollar = ft_strchr(dollar + ft_strlen(name), '$');
			free(name);
		}
		else
			dollar = ft_strchr(dollar + 1, '$');
	}
	if (expanded == NULL)
		expanded = ft_strdup(line);
	return (expanded);
}

char	*ft_expand_quotes(char *line)
{
	char	*parsed;

	parsed = line;
	return (parsed);
}

/*
 * ft_quotes_closed
 * if quotes (single or double) are closed, returns NULL
 * else (if not closed) returns position
 * of last unclosed quote (simple or double).
 */

char	*ft_quotes_closed(char *line)
{
	char	c;
	char	*s;
	char	*ss;

	s = line;
	while (s != NULL && *s != '\0')
	{
		if (*s == 042 || *s == 047)
		{
			c = *s;
			ss = s + 1;
			while (*ss != '\0' && *ss != c)
				++ss;
			if (*ss == '\0')
				return (s);
			else
				s = ss;
		}
		++s;
	}
	return (NULL);
}
