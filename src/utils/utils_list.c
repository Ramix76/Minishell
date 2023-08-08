/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 15:49:37 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/08/08 11:26:49 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_swap(void **a, void **b);

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
	t_list	*current;
	t_list	*min_node;
	t_list	*temp;

	current = list;
	while (current != NULL)
	{
		min_node = current;
		temp = current->next;
		while (temp != NULL)
		{
			if (*((char *)temp->content) < *((char *)min_node->content))
				min_node = temp;
			temp = temp->next;
		}
		if (min_node != current)
		{
			ft_swap((void **)&current->content, (void **)&min_node->content);
		}
		current = current->next;
	}
	return (EXIT_SUCCESS);
}

static void	ft_swap(void **a, void **b)
{
	void	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}
