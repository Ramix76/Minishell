/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_which.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 13:11:17 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/06/08 18:42:59 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "test.utils.h"

int	main(int argc, char **argv, const char **envp)
{
	char	*name;
	char	*path;
	char	*which;

	init_log(argc, argv, (char **) envp);
	path = ft_getenv("PATH", envp);
	printf("og_getenv: %s\n", getenv("PATH"));
	printf("og_getenv: %s\n", getenv(NULL));
	printf("ft_getenv: %s\n", path);
	name = "cat -e";
	which = ft_which(name, ft_getenv("PATH", envp));
	printf("ft_which: %s\n", which);
	free(which);
	printf("ft_which: %s\n", ft_which(name, NULL));
	printf("ft_which: %s\n", ft_which(NULL, path));
	return (0);
}
