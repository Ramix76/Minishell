/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 12:12:38 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/07/25 17:22:06 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_quotes_closed(char *line);

char	*ft_expand_quotes(char *line, t_data *data)
{
	char	*expanded;

	(void) data;
	expanded = line;
	if (ft_quotes_closed(expanded) != NULL)
		return (expanded);
	
	// other function ...

	return (expanded);
}

/*
 * ft_quotes_closed
 * if quotes (single or double) are closed, returns NULL
 * else (if not closed) returns position
 * of last unclosed quote (simple or double).
 */

static char	*ft_quotes_closed(char *line)
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
