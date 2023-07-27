/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exported.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 14:35:32 by framos-p          #+#    #+#             */
/*   Updated: 2023/07/27 17:03:08 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_combine_vars(char **env_vars, char **exported_vars);
static int	ft_env_count(char **env_vars);
static int	ft_exported_count(char **exported_vars);
static char	**ft_allocate_combined_vars(int env_count, int exported_count);

static int	ft_env_count(char **env_vars)
{
	int	count;

	count = 0;
	if (env_vars != NULL)
	{
		while (env_vars[count])
			count++;
	}
	return (count);
}

static int	ft_exported_count(char **exported_vars)
{
	int	count;

	count = 0;
	if (exported_vars != NULL)
	{
		while (exported_vars[count])
			count++;
	}
	return (count);
}

static char	**ft_allocate_combined_vars(int env_count, int exported_count)
{
	char	**combined_vars;
	int		total_count;

	total_count = env_count + exported_count;
	combined_vars = malloc(sizeof(char *) * (total_count + 1));
	if (combined_vars == NULL)
	{
		ft_fprintf(stderr, "Fatal Error\n");
		return (NULL);
	}
	return (combined_vars);
}

char	**ft_combine_vars(char **env_vars, char **exported_vars)
{
	int		env_count;
	int		exported_count;
	int		i;
	int		j;
	char	**combined_vars;

	env_count = ft_env_count(env_vars);
	exported_count = ft_exported_count(exported_vars);
	combined_vars = ft_allocate_combined_vars(env_count, exported_count);
	if (combined_vars == NULL)
		return (NULL);
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
	combined_vars[env_count + exported_count] = NULL;
	return (combined_vars);
}

void	ft_print_combined_vars(t_data *data)
{
	int		env_count;
	char	**env_copy;
	char	**exported_copy;
	char	**combined_vars;

	if (data->exported_vars == NULL)
	{ return; }
	else
		printf("no here\n");

	env_count = 0;
	if (data->envp != NULL)
	{
		while (data->envp[env_count])
			env_count++;
	}
	env_copy = ft_strduparr(data->envp);
	exported_copy = ft_strduparr(data->exported_vars);
	combined_vars = ft_combine_vars(env_copy, exported_copy);
	if (combined_vars != NULL)
	{
		ft_sort_vars(combined_vars);
		ft_print_sorted_vars(combined_vars);
		ft_free_vars(combined_vars);
	}
	ft_free_vars(env_copy);
	ft_free_vars(exported_copy);
}
