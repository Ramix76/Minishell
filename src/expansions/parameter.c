/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:32:15 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/08/22 13:07:19 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			*ft_expand_dollar(char *str, t_data *data);
static size_t	ft_expand_dollar_len(char *str, t_data *data);
static size_t	ft_resolve_len(char *ptr, t_data *data, size_t *len_ptr);
static int		ft_expand_dollar_value(char *expanded,
					size_t len, t_data *data);
static int		ft_modified_quote(int *quote_ptr, char *ptr);

char	*ft_expand_dollar(char *ptr, t_data *data)
{
	char			*expanded;
	size_t			i;
	const size_t	len = ft_expand_dollar_len(ptr, data);
	int				quote;

	i = 0;
	quote = '\0';
	expanded = (char *) ft_calloc(sizeof(char), len + 1);
	while (i < len)
	{
		if (ft_modified_quote(&quote, ptr) == 0
			&& (quote == '\0' || quote == 042) && *ptr == '$')
		{
			data->temp = ft_getname(ptr);
			if (data->temp != NULL)
			{
				ptr = ptr + ft_strlen(data->temp) + 1;
				i += ft_expand_dollar_value(expanded, len, data);
				continue ;
			}
		}
		expanded[i++] = *ptr++;
	}
	return (expanded);
}

static int	ft_modified_quote(int *quote_ptr, char *ptr)
{
	int	modified;
	int	quote;

	modified = 0;
	quote = *quote_ptr;
	if (quote == '\0' && (*ptr == 042 || *ptr == 047))
	{
		quote = *ptr;
		modified = 1;
	}
	else if (quote != '\0' && quote == *ptr)
	{
		quote = '\0';
		modified = 1;
	}
	if (modified == 1)
		*quote_ptr = quote;
	return (modified);
}

static int	ft_expand_dollar_value(char *expanded, size_t len, t_data *data)
{
	char	*name;
	char	*value;
	size_t	i;

	i = 0;
	name = data->temp;
	value = ft_getvalue(name, data);
	if (value != NULL)
	{
		ft_strlcat(expanded, value, len + 1);
		i += ft_strlen(value);
		--i;
	}
	free(data->temp);
	++i;
	return (i);
}

static size_t	ft_expand_dollar_len(char *ptr, t_data *data)
{
	int		quote;
	size_t	len;

	quote = '\0';
	len = 0;
	while (*ptr != '\0')
	{
		if (quote == '\0' && (*ptr == 042 || *ptr == 047))
			quote = *ptr;
		else if (quote != '\0' && quote == *ptr)
			quote = '\0';
		else if ((quote == '\0' || quote == 042) && *ptr == '$')
			ptr += ft_resolve_len(ptr, data, &len);
		++len;
		++ptr;
	}
	return (len);
}

static size_t	ft_resolve_len(char *ptr, t_data *data, size_t *len_ptr)
{
	char	*name;
	char	*value;
	size_t	len;

	len = *len_ptr;
	name = ft_getname(ptr);
	if (name != NULL)
	{
		--len;
		value = ft_getvalue(name, data);
		if (value != NULL)
			len += ft_strlen(value);
		*len_ptr = len;
		return (len = ft_strlen(name), free(name), len);
	}
	return (0);
}
