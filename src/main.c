/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 11:31:44 by framos-p          #+#    #+#             */
/*   Updated: 2023/06/07 17:42:54 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	init_args(int argc, char **argv, char **envp, t_data *data);

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	init_args(argc, argv, envp, &data);
	data.exit_code = shell_do(&data);
	return (data.exit_code);
}

static int	init_args(int argc, char **argv, char **envp, t_data *data)
{
	if (argc >= 2 && ft_strcmp(argv[1], "--version") == 0)
	{
		printf("%s\n", SH_VERSION);
		exit(EXIT_SUCCESS);
	}
	data->envp = envp;
	data->path = ft_getenv("PATH", (const char **) envp);
	data->exit_code = 0;
	return (EXIT_SUCCESS);
}

void	free_str_arr(char **split)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
	{
		free(split[i]);
		++i;
	}
}
