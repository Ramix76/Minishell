/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 12:21:08 by framos-p          #+#    #+#             */
/*   Updated: 2023/07/31 12:11:10 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(const char *comd, const char *dir)
{
	ft_fprintf(stderr, "%s: %s: %s: %s\n", SH_NAME, comd, dir, strerror(errno));
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
