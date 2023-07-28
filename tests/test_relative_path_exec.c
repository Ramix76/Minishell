/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_relative_path_exec.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 12:55:51 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/07/28 12:55:51 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	main(int argc, char **argv, char **envp)
{
	char	*cmd;

	(void) argc;
	++argv;
	cmd = argv[0];
	if (ft_execvpe((const char *) cmd, (const char **) argv,
			(const char **) envp) == -1)
		return (1);
	return (0);
}
