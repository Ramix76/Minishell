/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:45:44 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/06/13 20:46:03 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "test.utils.h"

char	*shell_expand(char *str)
{
	char	*expanded;

	expanded = str;
	return (expanded);
}

int	main(int argc, char **argv, char **envp)
{
	char	*str;

	init_log(argc, argv, envp);
	str = "visca \"barsa\"";
	ft_printf("%s\n", str);
	return (0);
}
