/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:32:15 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/08/08 11:04:27 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			*ft_expand_dollar(char *str, t_data *data);
static size_t	ft_expand_dollar_len(char *str, t_data *data);
static char		*ft_getname(char *ptr);
static char		*ft_getvalue(char *ptr, t_data *data);

char	*ft_expand_dollar(char *ptr, t_data *data)
{
	char	*expanded;
	size_t	i;
	size_t	len;
	int		quote;
	char	*name;
	char	*value;

	i = 0;
	len = ft_expand_dollar_len(ptr, data);
	quote = '\0';
	expanded = (char *) ft_calloc(sizeof(char), len + 1);
	while (i < len)
	{
		if (quote == '\0' && (*ptr == 042 || *ptr == 047))
		{
			expanded[i] = *ptr;
			quote = *ptr;
		}
		else if (quote != '\0' && quote == *ptr)
		{
			expanded[i] = *ptr;
			quote = '\0';
		}
		else if ((quote == '\0' || quote == 042) && *ptr == '$')
		{
			name = ft_getname(ptr);
			if (name != NULL)
			{
				value = ft_getvalue(name, data);
				if (value != NULL)
				{
					ft_strlcat(expanded, value, len + 1);
					i += ft_strlen(value);
					--i;
				}
				ptr = ptr + ft_strlen(name);
			}
			else
				expanded[i] = *ptr;
		}
		else
			expanded[i] = *ptr;
		++i;
		++ptr;
	}
	return (expanded);
}

static size_t	ft_expand_dollar_len(char *ptr, t_data *data)
{
	int		quote;
	size_t	len;
	char	*name;
	char	*value;

	quote = '\0';
	len = 0;
	while (*ptr != '\0')
	{
		if (quote == '\0' && (*ptr == 042 || *ptr == 047))
			quote = *ptr;
		else if (quote != '\0' && quote == *ptr)
			quote = '\0';
		else if ((quote == '\0' || quote == 042) && *ptr == '$')
		{
			name = ft_getname(ptr);
			if (name != NULL)
			{
				--len;
				value = ft_getvalue(name, data);
				if (value != NULL)
					len += ft_strlen(value);
				ptr = ptr + ft_strlen(name);
			}
		}
		++len;
		++ptr;
	}
	return (len);
}

/*
 * As in GNU's Bash Reference:
 * name: A word consisting solely of letters, numbers, and underscores,
 * and beginning with a letter or underscore.
 * Names are used as shell variable and function names.
 * Also referred to as an identifier.
 *
 * ft_getname(char *ptr)
 * returns name portion from string
 *
 */

static char	*ft_getname(char *ptr)
{
	char	*name;
	size_t	name_len;

	if (ptr == NULL || *ptr == '\0' || *ptr != '$')
		return (NULL);
	++ptr;
	name_len = 0;
	if (*ptr == '?')
		return (ft_strdup("?"));
	else if (*ptr == '\0' || (ft_isalpha(*ptr) == 0 && *ptr != '_'))
		return (NULL);
	while (ptr[name_len] != '\0' && (ft_isalnum(ptr[name_len]) != 0
			|| ptr[name_len] == '_'))
		++name_len;
	name = ft_strndup(ptr, name_len);
	return (name);
}

/*
 * Function gets variable's (word) pointed by ptr value.
 *
 * ft_getvalue(char *name, t_data *data)
 * no need to free
 *
 */

static char	*ft_getvalue(char *name, t_data *data)
{
	char	*value;

	if (ft_strcmp("?", name) == 0)
	{
		value = ft_strdup(ft_itoa(data->exit_code));
		return (value);
	}
	value = ft_getenv(name, (const char **) data->envp);
	if (value == NULL)
		value = "";
	return (value);
}
