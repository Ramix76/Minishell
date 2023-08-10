/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 12:54:40 by framos-p          #+#    #+#             */
/*   Updated: 2023/08/10 16:16:54 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_data *data)
{
	char		cwd[PATH_MAX];
	const char	*pwd_env;

	pwd_env = ft_getenv("PWD", (const char **)data->envp);
	if (getcwd(cwd, PATH_MAX) != NULL)
	{
		printf("%s\n", cwd);
		return ((data->exit_code = 0), EXIT_SUCCESS);
	}
	else if (pwd_env != NULL)
	{
		printf("%s\n", pwd_env);
		return ((data->exit_code = 0), EXIT_SUCCESS);
	}
	else
	{
		ft_fprintf(stderr, "%s: pwd: Failed to get current directory\n",
			SH_NAME);
		return ((data->exit_code = 1), EXIT_FAILURE);
	}
}
