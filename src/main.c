/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 11:31:44 by framos-p          #+#    #+#             */
/*   Updated: 2023/08/22 14:49:36 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		ft_init_args(int argc, char **argv);
static int		ft_init_data(int argc, char **argv, char **envp, t_data *data);
static void		ft_free_some_stuff(t_data *data);

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	g_exit_code = 0;
	ft_init_args(argc, argv);
	ft_init_data(argc, argv, envp, &data);
	ft_init_signals(0);
	if (argc > 2 && ft_strcmp("-c", argv[1]) == 0)
		ft_shell_do(&data, argv[2]);
	else
		ft_shell_loop(&data);
	ft_free_some_stuff(&data);
	return (data.exit_code);
}

static int	ft_init_args(int argc, char **argv)
{
	if (argc >= 2 && ft_strcmp(argv[1], "--version") == 0)
	{
		printf("%s, %s\n", SH_NAME, SH_VERSION);
		exit(EXIT_SUCCESS);
	}
	return (EXIT_SUCCESS);
}

static int	ft_init_data(int argc, char **argv, char **envp, t_data *data)
{
	(void) argc;
	(void) argv;
	ft_init_env(envp, data);
	data->exec_dir = (char *) malloc(sizeof(char) * PATH_MAX);
	data->exec_dir = getcwd(data->exec_dir, PATH_MAX);
	data->exit_code = 0;
	data->running = 1;
	data->in = STDIN_FILENO;
	data->out = STDOUT_FILENO;
	data->pipe = 0;
	data->home = NULL;
	data->str_exit_code = NULL;
	data->exported_vars = NULL;
	ft_shlvl(envp, data);
	ft_sethome(data);
	data->exported_vars = (char **) malloc(sizeof(char *) * (1 + 1));
	*data->exported_vars = NULL;
	return (EXIT_SUCCESS);
}

static void	ft_free_some_stuff(t_data *data)
{
	ft_free_str_arr(data->envp);
	ft_free_str_arr(data->exported_vars);
	free(data->home);
	free(data->exec_dir);
	if (data->str_exit_code != NULL)
		free(data->str_exit_code);
}
