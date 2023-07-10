/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 11:33:26 by framos-p          #+#    #+#             */
/*   Updated: 2023/06/28 16:22:32 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"

static int	find_var_index(char *var, char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(var, envp[i], ft_strlen(var)) == 0)
			return (i);
		i++;
	}
	return (EXIT_FAILURE);
}

static void	free_var_and_shift(int i, char **envp)
{
	free(envp[i]);
	while (envp[i + 1] != NULL)
	{
		envp[i] = envp[i + 1];
		i++;
	}
	envp[i] = NULL;
}

void	ft_unset(char *var, t_data *data)
{
	int	i;

	i = find_var_index(var, data->envp);
	if (i != EXIT_FAILURE)
		free_var_and_shift(i, data->envp);
}
