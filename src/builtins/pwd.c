/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 12:54:40 by framos-p          #+#    #+#             */
/*   Updated: 2023/06/02 14:37:30 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_pwd()
{
	char	*cwd;

	cwd = (char*)malloc(PATH_MAX * sizeof(char));
	if (cwd == NULL)
	{
		perror("malloc");
		return (EXIT_FAILURE);
	}
	if (getcwd(cwd, PATH_MAX) != NULL)
		printf("%s\n", cwd);
	else
	{
		perror("Error al obtener el directorio actual");
		free(cwd);
		return (EXIT_FAILURE);
	}
	free(cwd);
	return (EXIT_SUCCESS);
}
