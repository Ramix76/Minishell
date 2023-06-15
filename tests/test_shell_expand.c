/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_shell_expand.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:30:14 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/06/15 17:47:14 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "test.utils.h"

char	*shell_expand(char *line, t_data *data)
{
	char	*expanded;

	(void) data;
	(void) line;
	expanded = ft_strdup(line);
	return (expanded);
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
	while (len-- > 0)
		new_envp[len] = ft_strdup(envp[len]);
	new_envp[len] = NULL;
	data->envp = new_envp;
	return (EXIT_SUCCESS);
}

static int	init_data(int argc, char **argv, char **envp, t_data *data)
{
	(void) argc;
	(void) argv;
	init_env(envp, data);
	data->path = ft_getenv("PATH", (const char **) envp);
	if (data->path == NULL)
		data->path = _PATH_DEFPATH;
	data->exit_code = 0;
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	char	line[] = "echo $?";
	init_log(argc, argv, envp);
	init_data(argc, argv, envp, &data);
	ft_printf("%s\n", shell_expand(line, &data));
	return (0);
}
