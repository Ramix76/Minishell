/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 14:51:56 by framos-p          #+#    #+#             */
/*   Updated: 2023/08/14 16:41:56 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_process_export_token(char *token, t_data *data);
static int	ft_empty_values(char *t, t_data *data);
static char	*ft_concatenate_tokens(char *name, char *value, t_data *data);
static bool	ft_is_valid_var_name(const char *name);

int	ft_export(t_cmd *cmd, t_data *data)
{
	int	count;
	int	i;

	count = 0;
	while (cmd->tokens != NULL && cmd->tokens[count])
		count++;
	if (count < 2)
	{
		data->exit_code = 0;
		return (ft_print_combined_vars(data), EXIT_SUCCESS);
	}
	i = 0;
	while (++i < count)
		ft_process_export_token(cmd->tokens[i], data);
	data->exit_code = 0;
	return (EXIT_SUCCESS);
}

static int	ft_process_export_token(char *t, t_data *data)
{
	char	*name;
	char	*value;

	if (ft_strchr(t, '=') == NULL || *(ft_strchr(t, '=') + 1) == '\0')
		return (ft_empty_values(t, data));
	name = ft_strndup(t, ft_strchr(t, '=') - t);
	if (!ft_is_valid_var_name(name))
		return (ft_fprintf(stderr, "%s: export: '%s': not a valid identifier\n",
				SH_NAME, name), (data->exit_code = 1), EXIT_FAILURE);
	if (ft_strchr(name, '-') != NULL || ft_quotes_closed(name) != NULL)
		return (ft_fprintf(stderr, "%s: export: '%s': not a valid identifier\n",
				SH_NAME, name), (data->exit_code = 1), EXIT_FAILURE);
	value = ft_strdup(ft_strchr(t, '=') + 1);
	if (ft_getenv(name, (const char **) data->exported_vars) != NULL)
		ft_unsetenv(name, data->exported_vars);
	if (ft_strnstr(t, "+=", ft_strlen(t)) != NULL
		&& ft_strnstr(t, "+=", ft_strlen(t)) + 1 == ft_strchr(t, '='))
	{
		*(ft_strchr(name, '+')) = '\0';
		value = ft_concatenate_tokens(name, value, data);
	}
	ft_setenv(name, value, 1, &data->envp);
	free(name);
	data->exit_code = 0;
	return (free(value), EXIT_SUCCESS);
}

static int	ft_empty_values(char *t, t_data *data)
{
	char	*name;

	if (ft_strchr(t, '-') != NULL)
		return (ft_fprintf(stderr, "%s: export: `%s': not a valid identifier\n",
				SH_NAME, t), (data->exit_code = 1), EXIT_FAILURE);
	if (ft_strchr(t, '=') == NULL)
		name = ft_strdup(t);
	else
		name = ft_strndup(t, ft_strchr(t, '=') - t);
	if (ft_getenv(name, (const char **) data->exported_vars) != NULL)
		ft_unsetenv(name, data->exported_vars);
	if (ft_getenv(name, (const char **)data->envp) != NULL)
	{
		free(name);
		data->exit_code = 0;
		return (EXIT_SUCCESS);
	}
	ft_unsetenv(name, data->envp);
	if (ft_strchr(t, '=') == NULL)
		ft_setenv(name, "", 1, &data->exported_vars);
	else
		ft_setenv(name, "", 1, &data->envp);
	free(name);
	data->exit_code = 0;
	return (EXIT_SUCCESS);
}

static char	*ft_concatenate_tokens(char *name, char *value, t_data *data)
{
	char	*result;

	if (ft_getenv(name, (const char **)data->envp) != NULL)
	{
		result = ft_strjoin(ft_getenv(name, (const char **)data->envp), value);
		free(value);
		value = result;
	}
	return (value);
}

static bool	ft_is_valid_var_name(const char *name)
{
	const char	*invalid_chars;
	size_t		i;

	invalid_chars = "=-!@#$%^&*()_+[]{}|;:,.<>?/`~";
	i = 0;
	while (invalid_chars[i] != '\0')
	{
		if (ft_strchr(name, invalid_chars[i]) != NULL)
			return (false);
		i++;
	}
	if (ft_isdigit(name[0]))
		return (false);
	return (true);
}
