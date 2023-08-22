/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 14:09:15 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/08/20 14:09:15 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	ft_totalarrlen(char **arr);

char	*ft_arr2str(char **arr)
{
	int		i;
	char	*str;
	size_t	len;

	i = 0;
	str = NULL;
	len = ft_totalarrlen(arr);
	str = (char *) calloc(sizeof(char), len + 1);
	while (arr != NULL && arr[i] != NULL)
	{
		ft_strlcat(str, arr[i], len);
		ft_strlcat(str, " ", len);
		++i;
	}
	str[len] = '\0';
	return (str);
}

static size_t	ft_totalarrlen(char **arr)
{
	int		i;
	size_t	len;

	i = 0;
	len = 0;
	while (arr != NULL && arr[i] != NULL)
	{
		len += ft_strlen(arr[i]);
		++len;
		++i;
	}
	return (len);
}
