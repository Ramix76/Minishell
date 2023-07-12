/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:58:51 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/07/11 18:02:16 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_init_env(char **envp, t_data *data)
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

int	ft_shlvl(char **envp, t_data *data)
{
	int		sh_lvl;
	char	*shlvl;
	char	*temp;

	shlvl = ft_getenv("SHLVL", (const char **) envp);
	if (shlvl == NULL)
		sh_lvl = 0;
	else
		sh_lvl = ft_atoi(shlvl);
	temp = ft_itoa(++sh_lvl);
	ft_setenv("SHLVL", temp, 1, (char ***) &data->envp);
	free(temp);
	return (EXIT_SUCCESS);
}

int	ft_sethome(t_data *data)
{
	char	*home;

	home = ft_getenv("HOME", (const char **) data->envp);
	if (home == NULL)
	{
		// If this login name is the null string,
		// the tilde is replaced with the value of the HOME shell variable.
		// If HOME is unset, the home directory of the user executing the 
		// shell is substituted instead. Otherwise, the tilde-prefix
		// is replaced with the home directory associated with the 
		// specified login name.
		//
		// lstat -> userid of process.
		home = getlogin();
		//ft_setenv("HOME", home, 1, &data->envp);
	}
	return (EXIT_SUCCESS);
}
