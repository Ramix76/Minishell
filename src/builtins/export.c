/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 14:51:56 by framos-p          #+#    #+#             */
/*   Updated: 2023/07/10 17:58:26 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"

static bool	is_valid_var_format(const char *var)
{
	size_t	i;
	
	printf("%s\n", var);
	if (!var || var[0] == '\0' || var[0] == '-')
		return (false);
	if (var[0] != '_' && ft_isalpha(var[0]) == 0)
		return (false);
	printf("hey\n");
	i = 1;
	while (var[i] != '\0')
	{
		if (var[i] != '_' && ft_isalnum(var[i]) == 0)
			return (false);
		i++;
	}
	return (true);
}

static void	process_export_token(char *token, t_data *data)
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
	if (!is_valid_var_format(name))
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

	count = 0;
	while (cmd->tokens[count])
		count++;
	i = 1;
	while (i < count)
	{
		process_export_token(cmd->tokens[i], data);
		i++;
	}
}
