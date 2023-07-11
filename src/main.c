/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 11:31:44 by framos-p          #+#    #+#             */
/*   Updated: 2023/07/11 12:15:07 by framos-p         ###   ########.fr       */
/*   Updated: 2023/06/12 15:48:53 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	init_args(int argc, char **argv, char **envp);
static int	init_data(int argc, char **argv, char **envp, t_data *data);
static int	init_env(char **envp, t_data *data);

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	init_args(argc, argv, envp);
	init_data(argc, argv, envp, &data);
	data.exit_code = shell_do(&data);
	free_str_arr(data.envp);
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
	int		sh_lvl;
	char	*temp;

	(void) argc;
	(void) argv;
	init_env(envp, data);
	data->path = ft_getenv("PATH", (const char **) envp);
	if (data->path == NULL)
		data->path = _PATH_DEFPATH;
	sh_lvl = ft_atoi(ft_getenv("SHLVL", (const char **) envp));
	temp = ft_itoa(++sh_lvl);
	ft_setenv("SHLVL", temp, 1, (char ***) &data->envp);
	free(temp);
	data->exit_code = 0;
	data->exported_vars = NULL;
	return (EXIT_SUCCESS);
}

static int	init_env(char **envp, t_data *data)
{
	char	**new_envp;
	int		len;

	len = 0;
	while (envp[len] != NULL)
		++len;
	new_envp = (char **) malloc(sizeof(char *) * (len + 1));
	if (new_envp == NULL)
		return (EXIT_FAILURE);
	new_envp[len] = NULL;
	while (len-- > 0)
		new_envp[len] = ft_strdup(envp[len]);
	data->envp = new_envp;
	return (EXIT_SUCCESS);
}
