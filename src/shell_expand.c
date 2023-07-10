/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:45:44 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/07/06 16:21:54 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*shell_expand(char *line, t_data *data)
{
	char	*expanded;

	(void) data;
	(void) line;
	expanded = ft_strdup(line);
	return (expanded);
}

char	*ft_expand_quotes(char *line)
{
	char	*parsed;

	parsed = line;
	return (parsed);
}
