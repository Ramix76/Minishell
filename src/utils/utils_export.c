/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 12:19:32 by framos-p          #+#    #+#             */
/*   Updated: 2023/07/31 16:02:39 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_sorting_env(char **arr, size_t size);

void	ft_free_vars(char **vars)
{
	int	i;

	if (vars == NULL)
		return ;
	i = 0;
	while (vars[i])
	{
		free(vars[i]);
		i++;
	}
	free(vars);
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

void	ft_sort_vars(char **vars)
{
	int		count;
	int		start;
	int		end;
	char	*temp;

	count = 0;
	while (vars[count])
		count++;
	ft_sorting_env(vars, count);
	start = 0;
	end = count - 1;
	while (start < end)
	{
		temp = vars[start];
		vars[start] = vars[end];
		vars[end] = temp;
		start++;
		end--;
	}
}

void	ft_print_sorted_vars(char **vars)
{
	int		i;
	char	*name;
	char	*value;

	i = 0;
	while (vars[i])
	{
		name = ft_strndup(vars[i], ft_strchr(vars[i], '=') - vars[i]);
		value = ft_strchr(vars[i], '=') + 1;
		if (*value == '\0')
			printf("declare -x %s=\"\"\n", name);
		else
			printf("declare -x %s=\"%s\"\n", name, value);
		i++;
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
