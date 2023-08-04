/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 10:09:37 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/08/04 13:07:40 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_str_arr(char **split)
{
	int	i;

	if (split == NULL)
		return ;
	i = 0;
	while (split[i] != NULL)
	{
		free(split[i]);
		++i;
	}
	free(split);
}

char	**ft_strduparr(char **arr)
{
	int		count;
	char	**copy;

	count = 0;
	if (arr == NULL)
		return (NULL);
	while (arr[count] != NULL)
		++count;
	copy = (char **) malloc(sizeof(char *) * (count + 1));
	if (copy == NULL)
		return (NULL);
	copy[count] = NULL;
	while (count-- > 0 && arr[count] != NULL)
		copy[count] = ft_strdup(arr[count]);
	return (copy);
}

size_t	ft_arrlen(char **arr)
{
	size_t	len;

	len = 0;
	while (arr != NULL && arr[len] != NULL)
		++len;
	return (len);
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
