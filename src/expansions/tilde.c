/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:34:37 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/07/12 12:24:41 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_expand_tilde(char *line, t_data *data)
{
	char	*expanded;
	char	*tilde;

	(void) data;
	expanded = ft_strdup(line);
	tilde = ft_strchr(expanded, '~');
	while (tilde != NULL)
	{
		tilde = ft_strchr(expanded, '~');
	}
	return (expanded);
}

/*
int	main(void)
{
	char	*line;
	char	*expanded;

	line = "expand this shit ~";
	expanded = ft_expand_tilde(line, NULL);
	printf("%s\n", expanded);
	free(expanded);
	return (0);
}
*/
