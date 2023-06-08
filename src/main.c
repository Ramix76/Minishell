/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 11:31:44 by framos-p          #+#    #+#             */
/*   Updated: 2023/06/08 11:45:41 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	init_args(int argc, char **argv, char **envp);
static int	init_data(int argc, char **argv, char **envp, t_data *data);

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	init_args(argc, argv, envp);
	init_data(argc, argv, envp, &data);
	data.exit_code = shell_do(&data);
	return (data.exit_code);
}

static int	init_args(int argc, char **argv, char **envp)
{
	if (argc >= 2 && ft_strcmp(argv[1], "--version") == 0)
	{
		printf("%s\n", SH_VERSION);
		exit(EXIT_SUCCESS);
	}
	(void) envp;
	return (EXIT_SUCCESS);
}

static int	init_data(int argc, char **argv, char **envp, t_data *data)
{
	(void) argc;
	(void) argv;
	data->envp = envp;
	data->path = ft_getenv("PATH", (const char **) envp);
	if (data->path == NULL)
		data->path = _PATH_DEFPATH;
	data->exit_code = 0;
	return (EXIT_SUCCESS);
}
