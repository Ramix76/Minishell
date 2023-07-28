/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:45:44 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/07/27 11:03:43 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_shell_expand(char *line, t_data *data)
{
	char	*expanded;

	expanded = ft_expand_tilde(line, data);
	expanded = ft_expand_dollar(expanded, data);
	expanded = ft_expand_quotes(expanded, data);
	return (expanded);
}

//	expanded = ft_expand_asteric(expanded, data);
