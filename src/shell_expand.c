/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:45:44 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/07/11 11:53:23 by mpuig-ma         ###   ########.fr       */
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

char	*ft_strpjoin_replace(char *s1, char *s2, size_t p)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*strpjoin;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	if (p > len_s1)
		p = len_s1;
	strpjoin = (char *) malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (strpjoin == NULL)
		return (0);
	ft_bzero(strpjoin, len_s1 + len_s2 + 1);
	if (len_s1 > 0)
		ft_strlcat(strpjoin, s1, p + 1);
	ft_strlcat(strpjoin, s2, p + len_s2 + 1);
	if (len_s1 > 0)
		ft_strlcat(strpjoin, s1 + p + 1, p + len_s2 + len_s1 + 1);
	return (strpjoin);
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
			memmove(dollar + 1, dollar + 1 + name_len, ft_strlen(dollar + name_len));
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
