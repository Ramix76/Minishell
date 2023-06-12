/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_setenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:52:45 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/06/12 19:50:58 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "test.utils.h"

int	ft_setenv(const char *name, const char *value, int overwrite, const char **envp, t_data *data);
static int	init_env(char **envp, t_data *data);

static int	add(const char *name, const char *value, char **envp, t_data *data);
static int	rm(const char *name, char **envp);
static int	overwrite(const char *name, const char *value, const char **envp, t_data *data);

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	init_log(argc, argv, envp);
	init_env(envp, &data);
	rm("TERM_PROGRAM", envp);
	return (0);
}

static int	rm(const char *name, char **envp)
{
	int		len;
	char	*var_name;

	len = 0;
	var_name = ft_strjoin(name, "=");

	while (envp[len] != NULL)
	{
		if (ft_strncmp(envp[len], var_name, ft_strlen(var_name)) == 0)
		{
			free(envp[len]);
			++i;
		}
		ft_printf("%s\n", envp[len]);

		++i;
		++len;
	}
	free(var_name);
	return (EXIT_SUCCESS);
}

int	ft_setenv(const char *name, const char *value, int owr, const char **envp, t_data *data)
{
	char	*env_name;

	env_name = NULL;
	if (name == NULL)
		return (EXIT_FAILURE);
	else if (name != NULL && owr == 0)
		return (EXIT_SUCCESS);
	env_name = ft_getenv(name, envp);
	if (env_name == NULL)
	{
		add(name, value, (char **) envp, data);
	}
	else
	{
		if (owr != 0)
			overwrite(name, value, envp, data);
	}
	return (EXIT_SUCCESS);
}

static int	add(const char *name, const char *value, char **envp, t_data *data)
{
	int		len;
	char	**new_envp;

	len = 0;
	new_envp = NULL;
	while (envp[len] != NULL)
		++len;
	new_envp = (char **) realloc(envp, sizeof(char *) * (len + 2));
	if (new_envp == NULL)
		return (EXIT_FAILURE);
	new_envp[len] = (char *) name;
	(void) value;
	new_envp[len + 1] = NULL;
	data->envp = new_envp;
	return (EXIT_SUCCESS);
}

static int	overwrite(const char *name, const char *value, const char **envp, t_data *data)
{
	(void) name;
	(void) value;
	(void) envp;
	(void) data;
	return (EXIT_SUCCESS);
}

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
