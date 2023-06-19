/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 12:54:40 by framos-p          #+#    #+#             */
/*   Updated: 2023/06/13 16:30:42 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_pwd(void)
{
	char	*cwd;
	char	*logicalcwd;

	logicalcwd = ft_strrchr(cwd, '/');
	cwd = (char *) malloc(PATH_MAX * sizeof(char));
	if (cwd == NULL)
	{
		ft_fprintf(stderr, "Bas allocation\n");
		return (EXIT_FAILURE);
	}
	if (getcwd(cwd, PATH_MAX) != NULL)
	{
		if (logicalcwd != NULL)
		{
			*logicalcwd = '\0';
			printf("%s\n", cwd);
		}
	}
	free(cwd);
	return (EXIT_SUCCESS);
}
