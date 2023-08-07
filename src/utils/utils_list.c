/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 15:49:37 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/08/07 15:49:37 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_concat_list(t_list *list)
{
	size_t	len;
	char	*concat;
	t_list	*lst;

	len = 0;
	if (list == NULL)
		return (NULL);
	lst = list;
	while (lst != NULL)
	{
		len += ft_strlen(lst->content);
		lst = lst->next;
		++len;
	}
	concat = (char *) malloc(sizeof(char) * len);
	ft_memset(concat, '\0', len);
	lst = list;
	while (lst != NULL)
	{
		ft_strlcat(concat, lst->content, len);
		ft_strlcat(concat, " ", len);
		lst = lst->next;
	}
	return (concat);
}

int	ft_sort_list(t_list *list)
{
	(void) list;
	return (EXIT_SUCCESS);
}
