/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exported.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 14:35:32 by framos-p          #+#    #+#             */
/*   Updated: 2023/07/13 17:05:21 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_combine_vars(char **env_vars, char **exported_vars);
static void	ft_free_vars(char **vars);

static char	**ft_combine_vars(char **env_vars, char **exported_vars)
{
	int		env_count;
	int		exported_count;
	int		total_count;
	char	**combined_vars;
	int		i;
	int		j;

	env_count = 0;
	while (env_vars[env_count])
		env_count++;
	exported_count = 0;
	while (exported_vars[exported_count])
		exported_count++;
	total_count = env_count + exported_count;
	combined_vars = malloc(sizeof(char *) * (total_count + 1));
	if (combined_vars == NULL)
	{
		ft_fprintf(stderr, "Fatal Error\n");
		return (NULL);
	}
	i = 0;
	while (i < env_count)
	{
		combined_vars[i] = ft_strdup(env_vars[i]);
		i++;
	}
	j = 0;
	while (j < exported_count)
	{
		combined_vars[i + j] = ft_strdup(exported_vars[j]);
		j++;
	}
	combined_vars[total_count] = NULL;
	return (combined_vars);
}

static void	ft_free_vars(char **vars)
{
	int	i;

	i = 0;
	while (vars[i])
	{
		free(vars[i]);
		i++;
	}
	free(vars);
}

void	ft_print_combined_vars(t_data *data)
{
	int		env_count;
	char	**env_copy;
	char	**exported_copy;
	char	**combined_vars;

	env_count = 0;
	while (data->envp[env_count])
		env_count++;
	env_copy = ft_strduparr(data->envp);
	exported_copy = ft_strduparr(data->exported_vars);
	combined_vars = ft_combine_vars(env_copy, exported_copy);
	ft_sort_vars(combined_vars);
	ft_print_sorted_vars(combined_vars);
	ft_free_vars(env_copy);
	ft_free_vars(exported_copy);
	ft_free_vars(combined_vars);
}
