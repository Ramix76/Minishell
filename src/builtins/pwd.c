/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 12:54:40 by framos-p          #+#    #+#             */
/*   Updated: 2023/08/05 18:27:44 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_data *data)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX) != NULL)
	{
		printf("%s\n", cwd);
		data->exit_code = EXIT_SUCCESS;
		return (EXIT_SUCCESS);
	}
	ft_fprintf(stderr, "%s: pwd: Failed to get current directory\n", SH_NAME);
	return (EXIT_FAILURE);
}
