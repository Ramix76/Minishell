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
