/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:45:44 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/07/12 17:27:25 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_shell_expand(char *line, t_data *data)
{
	char	*expanded;
	char	*dollar;
	char	*temp;

	expanded = ft_expand_tilde(line, data);
	dollar = ft_strchr(expanded, '$');
	while (dollar != NULL)
	{
		temp = ft_expand_dollar(expanded, dollar, data);
		if (temp != expanded)
			free(expanded);
		expanded = temp;
		dollar = ft_strchr(expanded, '$');
	}
	return (expanded);
}
