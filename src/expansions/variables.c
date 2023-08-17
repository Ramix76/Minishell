/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 13:55:44 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/08/17 13:55:44 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*ft_getname(char *ptr)
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

char	*ft_getvalue(char *name, t_data *data)
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
