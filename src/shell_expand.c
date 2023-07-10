/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:45:44 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/07/10 13:05:40 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * ft_strpjoin()
 * joins str s2 into position p of str s1
 *
 * if s1's length is smaller than p, s2 is appended like the
 * regular strjoin()
 *
 * if s1 is NULL, 
 *
 * if s2 is NULL
 *
 */

char	*ft_strpjoin(char *s1, char *s2, size_t p)
{
	char	*segment_a;
	char	*segment_b;
	size_t	i;

	i = 0;
	segment_a = s1;
	while (i < p)
	{ ++segment_a; ++i; }
	(void) segment_b;
	(void) s2;
	return (NULL);
}

char	*shell_expand(char *line, t_data *data)
{
	char	*expanded;

	(void) data;
	(void) line;
	expanded = ft_strdup(line);
	return (ft_strpjoin(line, "hola", 2));
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
