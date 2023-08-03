/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 15:11:36 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/08/03 17:48:19 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_parse_operators(char **tokens);
static char	*ft_gettoken(char *str);
static char	*ft_getword(char *str);

char	**ft_parse2tokens(char *str)
{
	char	*word;
	char	**tokens;
	size_t	arr_len;

	tokens = NULL;
	arr_len = 0;
	while (str != NULL && *str != '\0')
	{
		word = ft_gettoken(str);
		if (word != NULL && ft_strcmp(" ", word) != 0)
		{
			++arr_len;
			tokens = (char **) ft_realloc(tokens, sizeof(char *) * arr_len,
					sizeof(char *) * (arr_len + 1));
			tokens[arr_len - 1] = ft_strtrim(word, " ");
			tokens[arr_len] = NULL;
		}
		str += ft_strlen(word);
		free(word);
	}
	tokens = ft_parse_operators(tokens);
	return (tokens);
}

static char	**ft_parse_operators(char **tokens)
{
	int		i;
	int		x;
	size_t	arr_len;
	char	**split;
	char	**merged;

	i = 0;
	arr_len = 0;
	merged = NULL;
	while (tokens != NULL && tokens[i] != NULL)
	{
		if (ft_strchr(METACHARACTERS, *(tokens[i])) == NULL)
		{
			++arr_len;
			merged = (char **) ft_realloc(merged, sizeof(char *) * arr_len,
					sizeof(char *) * (arr_len + 1));
			merged[arr_len - 1] = ft_strdup(tokens[i]);
			merged[arr_len] = NULL;
		}
		else
		{
			split = ft_split(tokens[i], ' ');
			x = ft_arrlen(split);
			arr_len += x;
			merged = (char **) ft_realloc(merged, sizeof(char *) * arr_len,
					sizeof(char *) * (arr_len + 1));
			while (x-- > 0)
			{
				printf("x: %d: %s\n", x, split[x]);
				merged[arr_len - x] = ft_strdup(split[x]);
			}
			merged[arr_len] = NULL;
		}
		++i;
	}
	return (merged);
}

static char	*ft_gettoken(char *str)
{
	size_t	len;
	char	*token;

	len = 0;
	if (ft_strchr(METACHARACTERS, *str) != NULL)
	{
		while (*(str + len) != '\0'
			&& ft_strchr(METACHARACTERS, *(str + len)) != NULL)
			++len;
		token = ft_strndup(str, len);
	}
	else
		token = ft_getword(str);
	return (token);
}

static char	*ft_getword(char *str)
{
	size_t	len;
	char	quote;
	char	*word;

	len = 0;
	quote = '\0';
	while (*(str + len) != '\0'
		&& ft_strchr(METACHARACTERS, *(str + len)) == NULL)
	{
		if (quote == '\0' && (*(str + len) == 042 || *(str + len) == 047))
			quote = *(str + len);
		else if (quote != '\0')
		{
			while (*(str + len) != '\0' && *(str + len) != quote)
				++len;
			if (*(str + len) != '\0' && *(str + len) == quote)
				quote = '\0';
		}
		if (*(str + len) != '\0')
			++len;
	}
	word = ft_strndup(str, len);
	return (word);
}
