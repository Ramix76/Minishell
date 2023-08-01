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
