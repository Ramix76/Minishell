/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:43:35 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/08/05 15:07:07 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define START	0
#define END		1

static int	ft_job_do(char **tokens, int start, int end, t_data *data);

int	ft_job_control(char **tokens, t_data *data)
{
	int		i;
	int		job[2];

	i = 0;
	while (tokens != NULL && tokens[i] != NULL)
	{
		job[START] = i;
		while (tokens[i] != NULL && ft_strcmp("|", tokens[i]) != 0)
			++i;
		if (tokens[i] == NULL)
			--i;
		if (*(tokens[i]) == '|')
			job[END] = i - 1;
		else
			job[END] = i;
		ft_job_do(tokens, job[START], job[END], data);
		++i;
	}
	return (EXIT_SUCCESS);
}

static int	ft_job_do(char **tokens, int start, int end, t_data *data)
{
	size_t	arr_len;
	char	**job;

	arr_len = end - start + 1;
	job = ft_arrndup(tokens, arr_len);
	if (job == NULL)
	{
		errno = ENOMEM;
		return (EXIT_FAILURE);
	}
	if (ft_redirections_do(job, data) == EXIT_FAILURE
		|| ft_redirections_rm(job) == EXIT_FAILURE
		|| ft_command_do(job, data) == EXIT_FAILURE)
	{
		ft_free_arr(job);
		return (EXIT_FAILURE);
	}
	ft_free_arr(job);
	return (EXIT_SUCCESS);
}

/*
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
		}
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
*/
