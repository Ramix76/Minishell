/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 12:12:38 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/08/04 13:07:19 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_expand_quotes(char *str, t_data *data)
{
	size_t	len;
	int		quote;
	char	*expanded;

	(void) data;
	len = 0;
	quote = '\0';
	expanded = (char *) malloc(sizeof(char) * ft_strlen(str) + 1);
	ft_memset(expanded, '\0', ft_strlen(str) + 1);
	if (str != NULL && ft_quotes_closed(str) == NULL)
	{
		while (*str != '\0')
		{
			if ((*str == 042 || *str == 047) && quote == '\0')
				quote = *str;
			else if ((*str == 042 || *str == 047) && quote == *str)
				quote = '\0';
			else
				expanded[len++] = *str;
			++str;
		}
	}
	return (expanded);
}
