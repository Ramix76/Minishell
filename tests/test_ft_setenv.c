/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_setenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:52:45 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/06/13 20:43:10 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "test.utils.h"

static int	init_env(char **envp, t_data *data)
{
	char	**new_envp;
	int		len;

	len = 0;
	while (envp[len] != NULL)
		++len;
	new_envp = (char **) malloc(sizeof(char *) * len);
	if (new_envp == NULL)
		return (EXIT_FAILURE);
	while (len-- > 0)
		new_envp[len] = ft_strdup(envp[len]);
	new_envp[len] = NULL;
	data->envp = new_envp;
	return (EXIT_SUCCESS);
}

static void	print_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		ft_printf("  %s\n", envp[i]);
		++i;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	init_log(argc, argv, envp);
	init_env(envp, &data);
	if (ft_unsetenv("PATH", data.envp) == EXIT_FAILURE)
		ft_fprintf(stderr, "ft_unset failed\n");
	if (ft_unsetenv("PKG_CONFIG_PATH", data.envp) == EXIT_FAILURE)
		ft_fprintf(stderr, "ft_unset failed\n");
	ft_setenv("USER", "me", 1, &data.envp);
	if (ft_setenv("TEST", "42", 1, &data.envp) == EXIT_FAILURE)
		ft_fprintf(stderr, "ft_setenv failed\n");
	if (ft_setenv("TEST", "0042", 1, &data.envp) == EXIT_FAILURE)
		ft_fprintf(stderr, "ft_setenv failed\n");
	ft_setenv("DYLD_LIBRARY_PATH", "verycool", 1, &data.envp);
	ft_setenv("TMPDIR", "verybool", 1, &data.envp);
	ft_setenv("USER", "thug", 1, &data.envp);
	print_env(data.envp);
}
