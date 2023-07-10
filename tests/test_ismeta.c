/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ismeta.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 16:45:12 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/06/19 17:22:02 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "test.utils.h"

int	main(int argc, char **argv)
{
	char	c;

	c = 0;
	init_log(argc, argv, NULL);
	while (c < 127)
	{
		if (ft_ismeta(c) != 0)
			printf("%03d: OK\n", c);
		++c;
	}
	return (0);
}
