/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 14:51:56 by framos-p          #+#    #+#             */
/*   Updated: 2023/06/29 16:21:21 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"

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
		if (var[i] == '_' || ft_isalnum(var[i]))
			return (false);
	}
	return (true);
}

void	ft_export(char *var, t_data *data)
{
	char	*value;
	char	*name;
	int		overwrite;

	overwrite = 1;
	name = ft_strdup(var);
	value = ft_strchr(name, '=');
	if (!is_valid_var_format(name))
	{
		ft_error(ERR_FORMAT, var);
		free(name);
		return ;
	}
	if (value != NULL)
	{
		*value = '\0';
		value++;
	}
	ft_setenv(name, value, 1, &data->envp);
	free(name);
}
