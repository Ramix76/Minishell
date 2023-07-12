/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 12:19:32 by framos-p          #+#    #+#             */
/*   Updated: 2023/07/12 12:20:35 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_sorted_env(char **envp_copy)
{
	int	i;

	i = 0;
	while (envp_copy[i])
		i++;
	i--;
	while (i >= 0)
	{
		printf("declare -x %s\n", envp_copy[i]);
		i--;
	}
}

void	ft_sorting_env(char **arr, size_t size)
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
