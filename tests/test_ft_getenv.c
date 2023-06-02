/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_getenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 16:43:29 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/06/02 18:32:45 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "test.utils.h"

int	main(int argc, char **argv, char **envp)
{
	init_log(argc, argv, envp);	
	printf("with envp: %s\n", ft_getenv("PATH", (const char **) envp));
	return (0);
}
