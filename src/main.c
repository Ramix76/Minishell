/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 11:31:44 by framos-p          #+#    #+#             */
/*   Updated: 2023/07/12 17:21:08 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_init_args(int argc, char **argv);
static int	ft_init_data(int argc, char **argv, char **envp, t_data *data);

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	ft_init_args(argc, argv);
	ft_init_data(argc, argv, envp, &data);
	data.exit_code = ft_shell_do(&data);
	ft_free_str_arr(data.envp);
	return (data.exit_code);
}

static int	ft_init_args(int argc, char **argv)
{
	if (argc >= 2 && ft_strcmp(argv[1], "--version") == 0)
	{
		printf("%s\n", SH_VERSION);
		exit(EXIT_SUCCESS);
	}
	return (EXIT_SUCCESS);
}

static int	ft_init_data(int argc, char **argv, char **envp, t_data *data)
{
	(void) argc;
	(void) argv;
	ft_init_env(envp, data);
	data->path = ft_getenv("PATH", (const char **) envp);
	if (data->path == NULL)
		data->path = _PATH_DEFPATH;
	data->exec_dir = (char *) malloc(sizeof(char) * PATH_MAX);
	data->exec_dir = getcwd(data->exec_dir, PATH_MAX);
	data->exit_code = 0;
	data->home = NULL;
	ft_shlvl(envp, data);
	ft_sethome(data);
	return (EXIT_SUCCESS);
}
