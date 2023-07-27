/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 14:51:56 by framos-p          #+#    #+#             */
/*   Updated: 2023/07/27 16:55:30 by framos-p         ###   ########.fr       */
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
	char	*temp;

	count = 0;
	while (data->exported_vars && data->exported_vars[count] != NULL)
	{
		if (strcmp(data->exported_vars[count], var) == 0)
			return ;
		count++;
	}
	new_exported_vars = ft_realloc(data->exported_vars,
			sizeof(char *) * (count + 1), (count + 2));
	if (new_exported_vars == NULL)
	{
		errno = ENOMEM;
		perror(SH_NAME);
		return ;
	}
	data->exported_vars = new_exported_vars;

	(void) temp;	
	//temp = ft_getenv(var, (const char **) data->exported_vars);
	//printf("temp: %s\n", temp);

	data->exported_vars[count] = ft_strdup(var);
	data->exported_vars[count + 1] = NULL;
}

static void	ft_process_variable_without_value(const char *var, t_data *data)
{
	//data->exported_vars = (char **) malloc(sizeof(char *) * 1);
	//data->exported_vars[0] = (char *) malloc(sizeof(char *) * 1);
	printf("var: %s\n", var);
	ft_setenv(var, "hey", 1, &data->exported_vars);
	//ft_add_exported_var(var, data);
	(void) ft_add_exported_var;
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
// posa aqui el cas de += //
	equal_sign = ft_strchr(token, '=');
	ft_setenv(token, token, 1, &data->exported_vars);
	//if (equal_sign == NULL || *(equal_sign + 1) == '\0')
	//	ft_process_variable_without_value(token, data);
	//else
	//	ft_process_variable_with_value(token, data);
	(void) ft_process_variable_without_value;
	(void) ft_process_variable_with_value;
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
		ft_print_combined_vars(data);
		return ;
	}
	i = 0;
	while (++i < count)
		ft_process_export_token(cmd->tokens[i], data);
}
