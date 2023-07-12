/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 11:33:26 by framos-p          #+#    #+#             */
/*   Updated: 2023/07/12 12:14:35 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_find_var_index(char *var, char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(var, envp[i], ft_strlen(var)) == 0)
			return (i);
		i++;
	}
	return (-1);
}

static void	ft_free_var_and_shift(int i, char **envp)
{
	free(envp[i]);
	while (envp[i + 1] != NULL)
	{
		envp[i] = envp[i + 1];
		i++;
	}
	envp[i] = NULL;
}

static void	ft_process_unset_token(char *token, t_data *data)
{
	int	index;

	index = ft_find_var_index(token, data->envp);
	if (index != -1)
		ft_free_var_and_shift(index, data->envp);
}

void	ft_unset(char **vars, t_data *data)
{
	size_t	count;
	size_t	i;

	count = 0;
	while (vars[count])
		count++;
	i = 0;
	while (i < count)
	{
		ft_process_unset_token(vars[i], data);
		i++;
	}
}
