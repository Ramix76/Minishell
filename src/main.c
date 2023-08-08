/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 11:31:44 by framos-p          #+#    #+#             */
/*   Updated: 2023/08/08 12:42:53 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		ft_init_args(int argc, char **argv);
static int		ft_init_data(int argc, char **argv, char **envp, t_data *data);
static int		ft_init_signals(void);
sig_atomic_t	g_running = 1;

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	ft_init_args(argc, argv);
	ft_init_data(argc, argv, envp, &data);
	ft_shell_do(&data);
	ft_free_str_arr(data.envp);
	ft_free_str_arr(data.exported_vars);
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
	data->path = ft_getenv("PATH", (const char **) envp);
	if (data->path == NULL)
		data->path = _PATH_DEFPATH;
	data->exec_dir = (char *) malloc(sizeof(char) * PATH_MAX);
	data->exec_dir = getcwd(data->exec_dir, PATH_MAX);
	data->exit_code = 0;
	data->in = STDIN_FILENO;
	data->out = STDOUT_FILENO;
	data->home = NULL;
	data->exported_vars = NULL;
	ft_shlvl(envp, data);
	ft_sethome(data);
	ft_init_signals();
	data->exported_vars = (char **) malloc(sizeof(char *) * (1 + 1));
	*data->exported_vars = NULL;
	return (EXIT_SUCCESS);
}

static int	ft_init_signals(void)
{
	struct sigaction	sa;

	g_running = 1;
	sa.sa_flags = SA_SIGINFO;
	sa.sa_handler = &ft_signal_handler;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	return (EXIT_SUCCESS);
}
