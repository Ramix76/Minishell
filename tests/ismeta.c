/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ismeta.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 16:45:12 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/06/19 18:26:03 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "test.utils.h"

int	main(int argc, char **argv)
{
	init_log(argc, argv, NULL);
	if (argc != 2)
		return (0);
	if (ismeta(*argv[1]) != 0)
		printf("OK\n");
	return (0);
}
