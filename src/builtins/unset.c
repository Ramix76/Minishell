/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 11:33:26 by framos-p          #+#    #+#             */
/*   Updated: 2023/08/10 16:17:06 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(t_cmd *cmd, t_data *data)
{
	size_t	count;
	size_t	i;
	char	**vars;

	vars = cmd->tokens;
	count = 0;
	while (vars[count])
		count++;
	i = 1;
	while (i < count)
	{
		ft_unsetenv(vars[i], data->envp);
		ft_unsetenv(vars[i], data->exported_vars);
		i++;
	}
	return (EXIT_SUCCESS);
}
