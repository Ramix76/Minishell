/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 14:51:56 by framos-p          #+#    #+#             */
/*   Updated: 2023/07/06 17:25:44 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"

/*
static bool	is_valid_var_format(const char *var)
{
	size_t	i;

	if (!var || var[0] == '\0' || var[0] == '=' || var[0] == '-'
			|| ft_strchr(var, '=') != ft_strrchr(var, '='))
			return (false);
	if (!(var[0] == '_' || ft_isalpha(var[0])))
		return (false);
	i = 1;
	while (var[i] != '\0')
	{
		if (!(var[i] == '_' || ft_isalnum(var[i]) || var[i] == '='))
			return (false);
		i++;
	}
	return (true);
}

static char	*get_value(const char *token)
{
	char	**tokens;
	char	*value;

	tokens = ft_split(token, '=');
	value = NULL;
	if (tokens[1] && tokens[1][0] == '=')
		value = ft_strdup(tokens[1] + 1);
	else
		value = ft_strdup("");
	free_str_arr(tokens);
	return (value);
}

static void	process_variable(const char *var, t_data *data)
{
	char	*name;
	char	*value;

	name = ft_split(var, '=')[0];
	value = get_value(var);
	ft_setenv(name, value, 1, &data->envp);
}

void	ft_export(t_cmd *cmd, t_data *data)
{
	size_t	i;

	i = 1;
	while (cmd->tokens[i])
	{
		if (is_valid_var_format(cmd->tokens[i]))
			process_variable(cmd->tokens[i], data);
		else
			ft_error(ERR_FORMAT, cmd->tokens[i]);
		i++;
	}
}
*/
static bool	is_valid_var_format(const char *var)
{
	size_t	i;

	if (!var || var[0] == '\0' || var[0] == '=' || var[0] == '-'
			|| ft_strchr(var, '=') == NULL)
			return (false);
	if (!(var[0] == '_' || ft_isalpha(var[0])))
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

void	ft_export(t_cmd *cmd, t_data *data)
{
	char	**tokens;
	char	*name;
	char	*value;
	size_t	i;
	size_t	count;

	count = 0;
	while (cmd->tokens[count])
		count++;
	i = 1;
	while (i < count)
	{
		name = cmd->tokens[i];
		if (!is_valid_var_format(name))
		{
			ft_error(ERR_FORMAT, name);
			++i;
			continue ;
		}
		tokens = ft_split(name, '=');
		if (tokens != NULL && tokens[0] != NULL)
		{
			name = tokens[0];
			if (tokens[1] != NULL && tokens[1][0] == '=')
				value = tokens[1] + 1;
			else
				value = "";
			ft_setenv(name, value, 1, &data->envp);
			free_str_arr(tokens);
		}
		i++;
	}
}
