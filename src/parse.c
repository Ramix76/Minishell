/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 15:11:36 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/08/03 10:40:02 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	return (tokens);
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
	char	quote;
	char	*word;
	size_t	len;

	quote = '\0';
	word = NULL;
	len = 0;
	if (*str == 042 || *str == 047)
		quote = *str;
	while (*(str + len) != '\0'
		&& ft_strchr(METACHARACTERS, *(str + len)) == NULL)
	{
		++len;
		if (quote != '\0')
		{
			while (*(str + len) != '\0' && *(str + len) != quote)
				++len;
			if (*(str + len) == quote)
				quote = '\0';
		}
	}
	word = ft_strndup(str, len);
	return (word);
}
