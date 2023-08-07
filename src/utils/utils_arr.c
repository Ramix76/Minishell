/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 10:09:37 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/08/05 15:06:47 by mpuig-ma         ###   ########.fr       */
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
		if (split[i] != NULL)
			free(split[i]);
		++i;
	}
	free(split);
}

char	**ft_arrdup(char **arr)
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

size_t	ft_arrlen(char **arr)
{
	size_t	len;

	len = 0;
	while (arr != NULL && arr[len] != NULL)
		++len;
	return (len);
}

char	**ft_arrndup(char **arr, size_t n)
{
	char	**dup;

	dup = (char **) malloc(sizeof(char *) * (n + 1));
	if (dup == NULL)
		return (NULL);
	dup[n] = NULL;
	while (n-- > 0)
		dup[n] = ft_strdup(arr[n]);
	return (dup);
}

void	ft_arr_rm_item(char **arr, int position)
{
	int		i;
	char	*temp;

	i = position;
	while (arr[i + 1] != NULL)
	{
		temp = arr[i];
		arr[i] = arr[i + 1];
		arr[i + 1] = temp;
		++i;
	}
	free(arr[i]);
	arr[i] = NULL;
}
