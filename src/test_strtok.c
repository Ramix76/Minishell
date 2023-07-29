/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_strtok.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 11:20:35 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/07/29 15:03:53 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_parse_tokens(char *line);
static char	*ft_word(char *str);

int	main(int argc, char **argv)
{
	char	*line;

	if (argc != 2)
		return (1);
	line = ft_strdup(argv[1]);
	char	**tokens = ft_parse_tokens(line);
	if (tokens == NULL)
		return (8);
	int i = 0;
	while (tokens != NULL && tokens[i] != NULL)
	{
		printf("w: %s\n", tokens[i]);
		++i;
	}
	free(line);
	return (0);
}

char	**ft_parse_tokens(char *str)
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
	return (tokens);
}

/*
int	main(int argc, char **argv)
{
	char	*line;
	char	*str;
	char	*word;

	if (argc != 2)
		return (1);
	line = ft_strdup(argv[1]);
	str = line;
	while (str != NULL && *str != '\0')
	{
		word = ft_word(str);
		printf("word: %s\n", ft_strtrim(word, " "));
		str += ft_strlen(word);
	}
	free(line);
	return (0);
}
*/

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
