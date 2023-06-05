/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 17:41:09 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/06/02 18:32:29 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.utils.h"

void	init_log(int argc, char **argv, char **envp)
{
	int	i;

	i = 0;
	while (i < argc)
	{
		printf(" %s ", argv[i]);
		++i;
	}
	printf("\n");
	(void) envp;
}
