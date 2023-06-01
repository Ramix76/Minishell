/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 12:54:40 by framos-p          #+#    #+#             */
/*   Updated: 2023/05/31 15:32:41 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/builtin.h"

int	ft_pwd()
{
	char	*cwd;

	cwd = (char*)malloc(PATH_MAX * sizeof(char));
	if (cwd == NULL)
	{
		perror("malloc");
		return (1);
	}
	if (getcwd(cwd, PATH_MAX) != NULL)
		printf("%s\n", cwd);
	else
	{
		perror("Error al obtener el directorio actual");
		free(cwd);
		return (1);
	}
	free(cwd);
	return (0);
}
