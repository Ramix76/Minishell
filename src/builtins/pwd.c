/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 12:54:40 by framos-p          #+#    #+#             */
/*   Updated: 2023/07/11 12:40:37 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_pwd(t_data *data)
{
	char	*cwd;

	cwd = ft_getenv("PWD", (const char **)data->envp);
	if (cwd != NULL)
	{
		printf("%s\n", cwd);
		return (EXIT_SUCCESS);
	}
	else
	{
		ft_fprintf(stderr, "Failed to retrieve current directory\n");
		return (EXIT_FAILURE);
	}
}
