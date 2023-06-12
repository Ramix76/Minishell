/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 12:58:40 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/06/12 14:48:50 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t size);

void	*ft_realloc(void *ptr, size_t size)
{
	void			*realloc_mem;
	unsigned char	*s;

	realloc_mem = NULL;
	if (ptr == NULL)
		realloc_mem = (void *) malloc(size);
	(void) s;
	return (NULL);
}

#include "test.utils.h"

int	main(int argc, char **argv, char **envp)
{
	char	*a;
	//char	*b;

	init_log(argc, argv, envp);
	a = (char *) malloc(sizeof(char) * 5);
	ft_memcpy(a, "hola", 5);
	ft_realloc(a, sizeof(char) * 10);
	ft_printf("%s\n", a);
	return (0);
}
