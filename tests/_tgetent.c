/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_tgetent.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 13:29:10 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/06/13 20:45:43 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include        <stdio.h>
#include        <curses.h>
#include        <term.h>
#include        <stdlib.h>

#include "test.utils.h"

int	main(int argc, char **argv, char **envp)
{
	const char	*name;
	char		*bp;
	char		*term;
	int			height;
	int			width;

	init_log(argc, argv, envp);
	bp = malloc(sizeof(*bp));
	name = "TERM";
	term = getenv(name);
	if (term == NULL)
		return (1);
	printf("My terminal is %s.\n", term);
	tgetent(bp, term);
	height = tgetnum ("li");
	width = tgetnum ("co");
	printf("H : %d\nL : %d\n", height, width);
	free(bp);
	return (0);
}
