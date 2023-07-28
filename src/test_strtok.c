/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_strtok.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 11:20:35 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/07/27 16:12:38 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_word(char *str);

int	main(void)
{
	char	*line;
	char	*str;
	char	*word;

	line = ft_strdup("\'hey  \'ls -la   \"$HOME\"  \'mo \"and more\"oree\'");
	str = line;
	while (str != NULL && *str != '\0')
	{
		word = ft_word(str);
		printf("word: %s\n", word);
		str += ft_strlen(word);
	}
	free(line);
	return (0);
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
			break ;
		}
		while (*(str + i) == delimiter && delimiter == ' ')
		{
			++i;
		}
	}
	word = ft_strndup(str, i);
	return (word);
}
