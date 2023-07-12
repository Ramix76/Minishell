/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 14:51:56 by framos-p          #+#    #+#             */
/*   Updated: 2023/07/12 12:14:25 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	ft_export(t_cmd *cmd, t_data *data)
{
	size_t	count;
	size_t	i;
	size_t	envp_count;
	char	**envp_copy;
	char	**exported_vars;

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
			ft_free_str_arr(envp_copy);
			ft_fprintf(stderr, "Fatal Error\n");
			return ;
		}
		ft_memcpy(envp_copy, data->envp, (envp_count + 1) * sizeof(char *));
		ft_sorting_env(envp_copy, envp_count);
		ft_print_sorted_env(envp_copy);
		ft_free_str_arr(envp_copy);
		return ;
	}
	i = 1;
	exported_vars = NULL; // Variable para almacenar las variables exportadas
	while (i < count)
	{
		ft_process_export_token(cmd->tokens[i], data);
		if (ft_strchr(cmd->tokens[i], '=') == NULL)
		{
			// La variable no tiene un valor asignado, guardarla en exported_vars
			if (exported_vars == NULL)
				exported_vars = ft_calloc(count - i + 1, sizeof(char *));
			exported_vars[i - 1] = ft_strdup(cmd->tokens[i]);
		}
		i++;
	}

	// Guardar las variables exportadas que no se han creado en el entorno
	if (exported_vars != NULL)
	{
		i = 0;
		while (exported_vars[i] != NULL)
		{
			// Aquí puedes realizar alguna acción con las variables exportadas que no se han creado en el entorno
			// Por ejemplo, imprimir las variables o guardarlas en una estructura de datos para su posterior uso
			printf("Variable exportada pero no creada en el entorno: %s\n", exported_vars[i]);
			free(exported_vars[i]);
			i++;
		}
		free(exported_vars);
	}
}

/*
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
			ft_free_str_arr(envp_copy);
			ft_fprintf(stderr, "Fatal Error\n");
			return ;
		}
		ft_memcpy(envp_copy, data->envp, (envp_count + 1) * sizeof(char *));
		ft_sorting_env(envp_copy, envp_count);
		ft_print_sorted_env(envp_copy);
		ft_free_str_arr(envp_copy);
		return ;
	}
	i = 1;
	while (i < count)
	{
		ft_process_export_token(cmd->tokens[i], data);
		i++;
	}
}*/
