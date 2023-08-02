/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:43:35 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/08/02 15:56:22 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define WR	1
#define RD	0

int	ft_job_control(char *line, t_data *data)
{
	int		i;
	char	*job;
	char	**split;
	int		fd;
	int		fildes[2];
	pid_t	pid;

	i = 0;
	split = ft_split(line, '|');
	fd = STDIN_FILENO;
	while (split != NULL && split[i] != NULL)
	{
		job = ft_strtrim(split[i], " ");
		//if (dup2(fd, STDIN_FILENO) != STDIN_FILENO)
		//	close(fd);
		if (pipe(fildes) == -1)
		{
			perror("pipe");
			exit(8);
		}
		pid = fork();
		if (pid == -1)
		{
			perror("pipes");
			exit(9);
		}
		if (pid == 0)
		{
			//if (i > 0)
			//	dup2(fildes[WR], STDOUT_FILENO);
			//close(fildes[RD]);
			ft_simple_command(job, data);
			//close(fildes[WR]);
			exit(EXIT_SUCCESS);
		}
		waitpid(pid, NULL, 0);
		//close(fildes[WR]);
		//fd = fildes[RD];
		free(job);
		++i;
	}
	//close(fd);
	rl_redisplay();
	ft_free_arr(split);
	return (EXIT_SUCCESS);
}
