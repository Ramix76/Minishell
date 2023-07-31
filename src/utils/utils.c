/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 10:09:37 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/07/27 17:31:02 by mpuig-ma         ###   ########.fr       */
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

	count = 0;
	if (arr == NULL)
		return (NULL);
	while (arr[count] != NULL)
		++count;
	copy = (char **) malloc(sizeof(char *) * (count + 1));
	if (copy == NULL)
		return (NULL);
	copy[count] = NULL;
	while (count-- > 0 && arr[count] != NULL)
		copy[count] = ft_strdup(arr[count]);
	return (copy);
}
