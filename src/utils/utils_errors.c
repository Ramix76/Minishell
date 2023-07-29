/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 12:21:08 by framos-p          #+#    #+#             */
/*   Updated: 2023/07/29 17:34:49 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(int error, const char *command, const char *dir)
{
	const char	*error_msg;

	error_msg = NULL;
	if (error == ENOENT || error == EACCES || error == ENOTDIR)
		error_msg = strerror(error);
	else if (error == NO_HOME)
		error_msg = NO_HOME_MSG;
	else if (error == ERR_CD)
		error_msg = ERR_CD_MSG;
	else if (error == ERR_PWD)
		error_msg = ERR_PWD_MSG;
	else if (error == ERR_OPWD)
		error_msg = ERR_OPWD_MSG;
	else if (error == ERR_FORMAT)
		error_msg = ERR_FORMAT_MSG;
	if (error_msg != NULL)
		ft_fprintf(stderr, "%s: %s: %s: %s\n", SH_NAME, command, dir, error_msg);
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
