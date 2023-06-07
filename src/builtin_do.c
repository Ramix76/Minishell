/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_do.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 17:31:50 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/06/07 17:35:50 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_do(char *exec_name)
{
	(void) exec_name;
	return (EXIT_SUCCESS);
}

	//if (isbuiltin(exec_name) == EXIT_SUCCESS)
	// execute it
	//else
	//	return (EXIT_FAILURE);
