/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 14:51:56 by framos-p          #+#    #+#             */
/*   Updated: 2023/07/29 12:52:19 by framos-p         ###   ########.fr       */
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

static int	ft_process_export_token(char *token, t_data *data)
{
	char	*equal_sign;
	char	*name;
	char	*value;

	equal_sign = ft_strchr(token, '=');
	if (equal_sign == NULL || *(equal_sign + 1) == '\0')
	{
		ft_unsetenv(token, data->envp);
		ft_setenv(token, "", 1, &data->exported_vars);
		return (EXIT_SUCCESS);
	}
	value = ft_strdup(ft_strchr(token, '=') + 1);
	name = ft_strndup(token, ft_strchr(token, '=') - token);
	if (ft_getenv(name, (const char **) data->exported_vars) != NULL)
		ft_unsetenv(name, data->exported_vars);
	if (ft_strnstr(token, "+=", ft_strlen(token)) != NULL
		&& ft_strnstr(token, "+=", ft_strlen(token)) + 1 == equal_sign)
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
