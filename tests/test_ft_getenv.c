/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_getenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 16:43:29 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/06/02 16:55:25 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	main(int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;
	printf("with envp: %s\n", ft_getenv("PATH", (const char **) envp));
	return (0);
}
