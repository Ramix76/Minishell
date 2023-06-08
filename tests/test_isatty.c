/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_isatty.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 13:10:59 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/06/08 13:29:35 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "test.utils.h"

int	main(int argc, char **argv, char **envp)
{
	init_log(argc, argv, envp);
	printf("result: %d\n", isatty(STDOUT_FILENO));
	printf("result: %d\n", isatty(7));
	printf("result: %s\n", ttyname(STDOUT_FILENO));
	return (0);
}
