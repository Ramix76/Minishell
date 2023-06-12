/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 12:12:12 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/06/12 15:51:08 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ft_gettingenv(char **envp)
{
	extern char		**environ;
	int				i;
	int				num_variables;

	i = 0;
	num_variables = 0;
	while (environ[num_variables] != NULL)
	{
		num_variables++;
	}
	*envp = *(char **)malloc(sizeof(char *) * (num_variables + 1));
	if (*envp == NULL)
	{
		printf("OUT OF MEMORY\n");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < num_variables)
	{
		(*envp)[i] = *environ[i];
		i++;
	}
	(*envp)[num_variables] = '\0';
}
