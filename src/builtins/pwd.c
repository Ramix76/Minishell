/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 12:54:40 by framos-p          #+#    #+#             */
/*   Updated: 2023/07/12 18:42:16 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		return (ft_error(ERR_CD, "", ""), EXIT_FAILURE);
}
