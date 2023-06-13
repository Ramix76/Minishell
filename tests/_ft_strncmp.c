/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_strncmp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 12:57:52 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/06/13 13:00:51 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "test.utils.h"

int	main(int argc, char **argv, char **envp)
{
	char	*test;

	init_log(argc, argv, envp);
	test = NULL;
	if (ft_strncmp(test, "~", 1) == 0)
		ft_printf("yes\n");
	return (0);
}
