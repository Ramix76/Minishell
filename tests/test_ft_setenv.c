/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_setenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:52:45 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/06/13 12:14:57 by mpuig-ma         ###   ########.fr       */
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

void	print_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
		ft_printf("  %s\n", envp[i++]);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	init_log(argc, argv, envp);
	init_env(envp, &data);
	if (ft_setenv("TEST", "42", 1, (const char **) data.envp) == EXIT_FAILURE)
		ft_fprintf(stderr, "ft_setenv failed\n");
	if (ft_setenv("TEST", "0042", 1, (const char **) data.envp) == EXIT_FAILURE)
		ft_fprintf(stderr, "ft_setenv failed\n");
	print_env(data.envp);
}
