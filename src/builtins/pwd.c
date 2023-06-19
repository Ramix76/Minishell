/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 12:54:40 by framos-p          #+#    #+#             */
/*   Updated: 2023/06/19 15:55:09 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_pwd(void)
{
	char	*cwd;

	cwd = (char *) malloc(PATH_MAX * sizeof(char));
	if (cwd == NULL)
	{
		ft_fprintf(stderr, "Bas allocation\n");
		return (EXIT_FAILURE);
	}
	if (getcwd(cwd, PATH_MAX) != NULL)
		printf("%s\n", cwd);
	free(cwd);
	return (EXIT_SUCCESS);
}
