/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 17:41:09 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/06/07 16:51:14 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.utils.h"

void	init_log(int argc, char **argv, char **envp)
{
	int	i;

	i = 0;
	while (i < argc)
	{
		printf(" \033[1;36m%s \033[0m", argv[i]);
		++i;
	}
	printf("\n");
	(void) envp;
}
