/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 14:51:56 by framos-p          #+#    #+#             */
/*   Updated: 2023/06/28 16:27:01 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"

static int	is_valid_var_format(const char *var)
{
	char	*equal_sign;

	equal_sign = ft_strchr(var, '=');
	return (equal_sign && equal_sign != var);
}

static void	update_var(const char *name, const char *value, char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(name, envp[i], ft_strlen(name)) == 0)
		{
			free(envp[i]);
			envp[i] = malloc(ft_strlen(name) + ft_strlen(value) + 2);
			if (!envp[i])
			{
				printf("Error de memoria\n");
				return ;
			}
			strcpy(envp[i], name);
			strcat(envp[i], "=");
			strcat(envp[i], value);
			return ;
		}
		i++;
	}
}

static void	add_var(const char *name, const char *value, char ***envp_ptr)
{
	int		envp_len;
	char	**envp;

	envp_len = 0;
	envp = *envp_ptr; 
	while (envp[envp_len] != NULL)
		envp_len++;
	envp = realloc(envp, sizeof(char *) * (envp_len + 2));
	if (!envp)
	{
		printf("Error de memoria\n");
		return ;
	}
	envp[envp_len] = malloc(ft_strlen(name) + ft_strlen(value) + 2);
	if (!envp[envp_len])
	{
		printf("Error de memoria\n");
		return ;
	}
	strcpy(envp[envp_len], name);
	strcat(envp[envp_len], "=");
	strcat(envp[envp_len], value);
	envp[envp_len + 1] = NULL;
	*envp_ptr = envp;
}

void	ft_export(char *var, t_data *data)
{
	char	*name;
	char	*value;

	name = ft_strdup(var);
	value = ft_strchr(name, '=');
	if (!is_valid_var_format(var))
	{
		printf("Error: Formato de variable incorrecto\n");
		free(name);
		return ;
	}
	if (value != NULL)
	{
		*value = '\0';
		value++;
	}
	update_var(name, value, data->envp);
	if ((data->envp)[0] == NULL)
		add_var(name, value, &data->envp);
	free(name);
}
