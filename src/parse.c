/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 15:11:36 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/08/02 12:04:00 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_word(char *str);

char	**ft_parse2tokens(char *str)
{
	char	*word;
	char	**tokens;
	size_t	arr_len;

	tokens = NULL;
	arr_len = 0;
	while (str != NULL && *str != '\0')
	{
		word = ft_word(str);
		++arr_len;
		tokens = (char **) ft_realloc(tokens, sizeof(char *) * arr_len,
				sizeof(char *) * (arr_len + 1));
		tokens[arr_len - 1] = ft_strtrim(word, " ");
		tokens[arr_len] = NULL;
		str += ft_strlen(word);
		free(word);
	}
	int i = 0;
	while (tokens[i] != NULL)
	{
		printf("t: %s\n", tokens[i]);
		++i;
	}
	return (tokens);
}

static char	*ft_word(char *str)
{
	char	*word;
	char	delimiter;
	int		i;

	i = 0;
	delimiter = 040;
	if (*str == 042 || *str == 047)
		delimiter = *str;
	while (*(str + i) != '\0')
	{
		++i;
		if (*(str + i) == delimiter)
		{
			++i;
			if (*(str + i) == ' ')
				while (*(str + i) != '\0' && *(str + i) == ' ')
					++i;
			break ;
		}
		while (*(str + i) == delimiter && delimiter == ' ')
			++i;
	}
	word = ft_strndup(str, i);
	return (word);
}
