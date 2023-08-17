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
