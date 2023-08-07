/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 17:55:21 by framos-p          #+#    #+#             */
/*   Updated: 2023/07/31 17:58:20 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd_ultra_specific_situation(void)
{
	ft_fprintf(stderr, "cd: error retrieving current directory: ");
	ft_fprintf(stderr, "getcwd: access parent directories: %s\n",
		strerror(errno));
	return (EXIT_FAILURE);
}

int	ft_cd_check_arguments(t_cmd *cmd)
{
	int			i;

	i = -1;
	cmd->tokens_count = 0;
	while (cmd->tokens[++i] != NULL)
		cmd->tokens_count++;
	if (cmd->tokens_count - 1 > 2)
		return (ft_fprintf(stderr, "%s: %s: No such file or directory\n",
				SH_NAME, cmd->tokens[0], EXIT_FAILURE));
	return (EXIT_SUCCESS);
}
