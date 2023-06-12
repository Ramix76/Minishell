/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:45:44 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/06/12 17:36:10 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*shell_expand(char *str)
{
	char	*expanded;

	expanded = str;
	return (expanded);
}

/*
#include "test.utils.h"

int	main(int argc, char **argv, char **envp)
{
	char	*str;

	init_log(argc, argv, envp);
	str = "visca \"barsa\"";
	ft_printf("%s\n", str);
	return (0);
}
*/
