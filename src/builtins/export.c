/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 14:51:56 by framos-p          #+#    #+#             */
/*   Updated: 2023/07/29 17:25:18 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_concatenate_tokens(char *name, char *value, t_data *data);
static int	ft_process_export_token(char *token, t_data *data);

int	ft_export(t_cmd *cmd, t_data *data)
{
	int	count;
	int	i;

	count = 0;
	while (cmd->tokens[count])
		count++;
	if (count == 1)
	{
		ft_print_combined_vars(data);
		return (EXIT_SUCCESS);
	}
	i = 0;
	while (++i < count)
		ft_process_export_token(cmd->tokens[i], data);
	return (EXIT_SUCCESS);
}

static int	ft_process_export_token(char *t, t_data *data)
{
	char	*name;
	char	*value;

	if (ft_strchr(t, '=') == NULL || *(ft_strchr(t, '=') + 1) == '\0')
	{
		if (ft_getenv(t, (const char **)data->envp) != NULL)
			return (EXIT_SUCCESS);
		ft_unsetenv(t, data->envp);
		ft_setenv(t, "", 1, &data->exported_vars);
		return (EXIT_SUCCESS);
	}
	value = ft_strdup(ft_strchr(t, '=') + 1);
	name = ft_strndup(t, ft_strchr(t, '=') - t);
	if (ft_getenv(name, (const char **) data->exported_vars) != NULL)
		ft_unsetenv(name, data->exported_vars);
	if (ft_strnstr(t, "+=", ft_strlen(t)) != NULL
		&& ft_strnstr(t, "+=", ft_strlen(t)) + 1 == ft_strchr(t, '='))
	{
		*(ft_strchr(name, '+')) = '\0';
		value = ft_concatenate_tokens(name, value, data);
	}
	ft_setenv(name, value, 1, &data->envp);
	free(value);
	free(name);
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
