/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:34:37 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/08/03 12:33:00 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_expand_tilde(char *str, t_data *data)
{
	char	*temp;
	char	*expanded;

	expanded = ft_strdup(str);
	if (str != NULL && *str == 0176)
	{
		if (*(str + 1) == '\0' || *(str + 1) == '/')
		{
			temp = expanded;
			expanded = ft_strpjoin_replace(expanded, data->home, 0);
			free(temp);
		}
	}
	return (expanded);
}
