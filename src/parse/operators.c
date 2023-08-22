/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 11:44:48 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/08/04 13:01:52 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	ft_getnewlen(char **arr);
static int		ft_appendarr(char **dst, char *src, int *position);
static size_t	ft_count_words(char const *s, char c);

char	**ft_parse_operators(char **tokens)
{
	int		i;
	int		position;
	size_t	arr_len;
	char	**merged;

	i = 0;
	position = 0;
	arr_len = ft_getnewlen(tokens);
	merged = (char **) malloc(sizeof(char *) * (arr_len + 1));
	ft_memset(merged, '\0', arr_len + 1);
	while (tokens != NULL && tokens[i] != NULL)
	{
		ft_appendarr(merged, tokens[i], &position);
		++i;
	}
	merged[position] = NULL;
	free(tokens);
	return (merged);
}

static int	ft_appendarr(char **merged, char *token, int *position)
{
	int		j;
	char	**split;

	j = 0;
	if (ft_strchr(METACHARACTERS, *token) == NULL)
	{
		merged[*position] = token;
		*position = *position + 1;
	}
	else
	{
		split = ft_split(token, ' ');
		j = ft_arrlen(split);
		while (j-- > 0)
			merged[*position + j] = split[j];
		*position = *position + ft_count_words(token, ' ');
		free(split);
	}
	return (EXIT_SUCCESS);
}

static size_t	ft_getnewlen(char **arr)
{
	int		i;
	size_t	arr_len;

	i = 0;
	arr_len = 0;
	while (arr != NULL && arr[i] != NULL)
	{
		if (ft_strchr(METACHARACTERS, *(arr[i])) == NULL)
			++arr_len;
		else
			arr_len += ft_count_words(arr[i], ' ');
		++i;
	}
	return (arr_len);
}

static size_t	ft_count_words(char const *s, char c)
{
	size_t	i;
	size_t	words;

	i = 0;
	words = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			words++;
		i++;
	}
	return (words);
}
