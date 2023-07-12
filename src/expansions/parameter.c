/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:32:15 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/07/11 16:39:43 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_getname(char *ptr);
static char	*ft_getvar(char	*ptr, t_data *data);

char	*ft_expand_dollar(char *expanded, char *dollar, t_data *data)
{
	char	*name;
	char	*value;
	char	*temp;
	size_t	name_len;
	size_t	p;

	name = ft_getname(dollar);
	if (name != NULL)
	{
		name_len = ft_strlen(name);
		value = ft_getvar(name, data);
		ft_memmove(dollar + 1, dollar + 1 + name_len,
			ft_strlen(dollar + name_len));
		p = ft_strchr(expanded, '$') - expanded;
		temp = ft_strpjoin_replace(expanded, value, p);
		expanded = temp;
		free(name);
	}
	return (expanded);
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
	if (*ptr == '\0' && (ft_isalpha(*ptr) == 0 || *ptr != '_'))
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
 * ft_getvar(char *name, t_data *data)
 * no need to free
 *
 */

static char	*ft_getvar(char	*name, t_data *data)
{
	char	*value;

	value = ft_getenv(name, (const char **) data->envp);
	if (value == NULL)
		value = "";
	return (value);
}
