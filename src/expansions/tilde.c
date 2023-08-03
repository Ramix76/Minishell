/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:34:37 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/08/03 11:03:42 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_expand_tilde(char *line, t_data *data)
{
	char	*expanded;
	char	*temp;
	char	*tilde;
	size_t	p;

	if (data->home == NULL)
		data->home = "";
	expanded = ft_strdup(line);
	tilde = ft_strchr(expanded, '~');
	while (tilde != NULL)
	{
		p = ft_strchr(expanded, '~') - expanded;
		temp = ft_strpjoin_replace(expanded, data->home, p);
		free(expanded);
		expanded = temp;
		tilde = ft_strchr(expanded, '~');
	}
	free(line);
	return (expanded);
}
