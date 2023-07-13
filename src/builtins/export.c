/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 14:51:56 by framos-p          #+#    #+#             */
/*   Updated: 2023/07/13 11:58:02 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_add_exported_var(const char *var, t_data *data);
static void	ft_process_variable_without_value(const char *var, t_data *data);
static void	ft_process_variable_with_value(const char *var, t_data *data);
static void	ft_process_export_token(char *token, t_data *data);

static void	ft_add_exported_var(const char *var, t_data *data)
{
	int		count;
	char	**new_exported_vars;

	count = 0;
	while (data->exported_vars && data->exported_vars[count] != NULL)
		count++;
	new_exported_vars = ft_realloc(data->exported_vars,
			sizeof(char *) * (count + 1), sizeof(char *) * (count + 2));
	if (new_exported_vars == NULL)
	{
		ft_fprintf(stderr, "Fatal Error\n");
		return ;
	}
	data->exported_vars = new_exported_vars;
	data->exported_vars[count] = ft_strdup(var);
	data->exported_vars[count + 1] = NULL;
}

static void	ft_process_variable_without_value(const char *var, t_data *data)
{
	ft_add_exported_var(var, data);
}

static void	ft_process_variable_with_value(const char *var, t_data *data)
{
	char	*equal_sign;
	size_t	name_length;
	char	*name;
	char	*value;

	equal_sign = ft_strchr(var, '=');
	name_length = equal_sign - var;
	name = ft_strndup(var, name_length);
	value = equal_sign + 1;
	if (!ft_is_valid_var_format(name))
	{
		ft_error(ERR_FORMAT, "export", name);
		free(name);
		return ;
	}
	ft_setenv(name, value, 1, &data->envp);
	free(name);
}

static void	ft_process_export_token(char *token, t_data *data)
{
	char	*equal_sign;

	equal_sign = ft_strchr(token, '=');
	if (equal_sign == NULL)
		ft_process_variable_without_value(token, data);
	else
		ft_process_variable_with_value(token, data);
}

void	ft_export(t_cmd *cmd, t_data *data)
{
	int	count;
	int	i;

	count = 0;
	while (cmd->tokens[count])
		count++;
	if (count == 1)
	{
		ft_print_env_vars(data);
		if (data->exported_vars != NULL)
			ft_print_exported_vars(data);
		return ;
	}
	i = 0;
	while (++i < count)
		ft_process_export_token(cmd->tokens[i], data);
}
