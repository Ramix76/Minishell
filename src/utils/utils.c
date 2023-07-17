/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 10:09:37 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/07/17 14:08:08 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_str_arr(char **split)
{
	int	i;

	if (split == NULL)
		return ;
	i = 0;
	while (split[i] != NULL)
	{
		free(split[i]);
		++i;
	}
	free(split);
}

char	**ft_strduparr(char **arr)
{
	int		count;
	char	**copy;
	int		i;

	if (arr == NULL)
		return (NULL);
	count = 0;
	while (arr[count])
		count++;
	copy = malloc(sizeof(char *) * (count + 1));
	if (copy == NULL)
	{
		ft_fprintf(stderr, "Fatal Error\n");
		return (NULL);
	}
	i = 0;
	while (i < count)
	{
		copy[i] = ft_strdup(arr[i]);
		i++;
	}
	copy[count] = NULL;
	return (copy);
}
