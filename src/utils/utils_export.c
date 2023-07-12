/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 12:19:32 by framos-p          #+#    #+#             */
/*   Updated: 2023/07/12 16:31:24 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_sorted_env(char **envp_copy)
{
	int		i;
	char	*equal_sign;
	size_t	name_length;
	char	*name;
	char	*value;

	i = 0;
	while (envp_copy[i])
		i++;
	i--;
	while (i >= 0)
	{
		equal_sign = ft_strchr(envp_copy[i], '=');
		if (equal_sign != NULL)
		{
			name_length = equal_sign - envp_copy[i];
			name = ft_strndup(envp_copy[i], name_length);
			value = equal_sign + 1;
			if (ft_is_valid_var_format(name))
				printf("declare -x %.*s=\"%s\"\n", (int)name_length, name, value);
			free(name);
		}
		i--;
	}
}

void	ft_sorting_env(char **arr, int size)
{
	int	i;
	int	j;
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

void	ft_print_env_vars(t_data *data)
{
	int	envp_count;
	char	**envp_copy;

	envp_count = 0;
	while (data->envp[envp_count])
		envp_count++;
	envp_copy = malloc(sizeof(char *) * (envp_count + 1));
	if (envp_copy == NULL)
	{
		ft_fprintf(stderr, "Fatal Error\n");
		return ;
	}
	ft_memcpy(envp_copy, data->envp, (envp_count + 1) * sizeof(char *));
	ft_sorting_env(envp_copy, envp_count);
	ft_print_sorted_env(envp_copy);
	free(envp_copy);
}

void	ft_print_exported_vars(t_data *data)
{
	int	exported_count;

	exported_count = 0;
	while (data->exported_vars[exported_count])
	{
		printf("declare -x %s\n", data->exported_vars[exported_count]);
		exported_count++;
	}
}

bool	ft_is_valid_var_format(const char *var)
{
	int	i;

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
