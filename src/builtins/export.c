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

/* 
 * MISSING:
 * check if name is already in data->envp or data->exported_vars!
 *
 */

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
		ft_setenv(token, "", 1, &data->exported_vars);
		return (EXIT_SUCCESS);
	}
	if (ft_strnstr(token, "+=", ft_strlen(token)) != NULL
		&& ft_strnstr(token, "+=", ft_strlen(token)) + 1 == equal_sign)
	{
		name = ft_strndup(token, ft_strchr(token, '=') - token - 1);
		value = ft_strchr(token, '=') + 1;
	}
	else
	{
		name = ft_strndup(token, ft_strchr(token, '=') - token);
		value = ft_strchr(token, '=') + 1;
	}
	ft_setenv(name, value, 1, &data->envp);
	free(name);
	return (EXIT_SUCCESS);
}
