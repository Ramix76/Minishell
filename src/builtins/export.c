/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 14:51:56 by framos-p          #+#    #+#             */
/*   Updated: 2023/07/11 13:02:44 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"

static bool	ft_is_valid_var_format(const char *var)
{
	size_t	i;
	
	if (!var || var[0] == '\0' || var[0] == '-')
		return (false);
	if (var[0] != '_' && ft_isalpha(var[0]) == 0)
		return (false);
	i = 1;
	while (var[i] != '\0')
	{
		if (var[i] != '_' && ft_isalnum(var[i]) == 0)
			return (false);
		i++;
	}
	return (true);
}

static void	ft_process_export_token(char *token, t_data *data)
{
	char	*name;
	char	*value;
	char	*equal_sign;
	size_t	name_length;

	equal_sign = ft_strchr(token, '=');
	if (equal_sign == NULL)
		return ;
	name_length = equal_sign - token;
	name = ft_strndup(token, name_length);
	value = equal_sign + 1;
	if (!ft_is_valid_var_format(name))
	{
		ft_error(ERR_FORMAT, name);
		free(name);
		return ;
	}
	ft_setenv(name, value, 1, &data->envp);
	free(name);
}

static void	ft_print_sorted_env(char **envp_copy)
{
	size_t	i;

	i = 0;
	while (envp_copy[i])
	{
		ft_putstr_fd(envp_copy[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
}

static void	ft_sorting_env(char **arr, size_t size)
{
	size_t	i;
	size_t	j;
	char	*temp;

	i = 0;
	while (i < size)
	{
		j = i + 1;
		while (j < size)
		{
			if (ft_strcmp(arr[i], arr[j]) < 0)
			{
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
			j++;
		}
		i++;
	}
}

void	ft_export(t_cmd *cmd, t_data *data)
{
	size_t	count;
	size_t	i;
	size_t	envp_count;
	char	**envp_copy;

	count = 0;
	while (cmd->tokens[count])
		count++;
	if (count == 1)
	{
		envp_count = 0;
		while (data->envp[envp_count])
			envp_count++;
		envp_copy = malloc(sizeof(char *) * (envp_count + 1));
		if (envp_copy == NULL)
		{
			free_str_arr(envp_copy);
			ft_fprintf(stderr, "Fatal Error\n");
			return ;
		}
		ft_memcpy(envp_copy, data->envp, (envp_count + 1) * sizeof(char *));
		ft_sorting_env(envp_copy, envp_count);
		ft_print_sorted_env(envp_copy);
		free_str_arr(envp_copy);
		return ;
	}
	i = 1;
	while (i < count)
	{
		ft_process_export_token(cmd->tokens[i], data);
		i++;
	}
}
