/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 12:12:38 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/08/03 15:51:15 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_expand_quotes(char *str)
{
	size_t	len;
	int		quote;
	char	*expanded;

	len = 0;
	quote = '\0';
	expanded = (char *) malloc(sizeof(char) * ft_strlen(str) + 1);
	ft_memset(expanded, '\0', ft_strlen(str) + 1);
	if (str != NULL && ft_quotes_closed(str) == NULL)
	{
		while (*str != '\0')
		{
			if ((*str == 042 || *str == 047) && quote == '\0')
				quote = *str;
			else if ((*str == 042 || *str == 047) && quote == *str)
				quote = '\0';
			else
				expanded[len++] = *str;
			++str;
		}
	}
	return (expanded);
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
