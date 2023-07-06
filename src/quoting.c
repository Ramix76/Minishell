/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 16:11:06 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/07/06 16:11:32 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * ft_quotes_closed
 * if quotes (single or double) are closed, returns NULL
 * else (if not closed) returns position of last unclosed quote (simple or double).
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
