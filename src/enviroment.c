/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:58:51 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/07/12 17:27:09 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdbool.h>

static char	*ft_gethome_fstab(void);

int	ft_init_env(char **envp, t_data *data)
{
	char	**new_envp;
	int		len;

	len = 0;
	while (envp != NULL && envp[len] != NULL)
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
	if (shlvl == NULL || *shlvl == '\0')
		sh_lvl = 0;
	else
		sh_lvl = ft_atoi(shlvl);
	if (sh_lvl < 0)
		sh_lvl = -1;
	else if (sh_lvl > 999)
	{
		ft_fprintf(stderr,
			"%s: warning: shell level (%d) too high, resetting to 1",
			SH_NAME, sh_lvl + 1);
		sh_lvl = 0;
	}
	temp = ft_itoa(++sh_lvl);
	ft_setenv("SHLVL", temp, 1, &data->envp);
	free(temp);
	return (EXIT_SUCCESS);
}

/* 
 * As in GNU's Bash Reference:
 * If this login name is the null string,
 * the tilde is replaced with the value of the HOME shell variable.
 * If HOME is unset, the home directory of the user executing the
 * shell is substituted instead. Otherwise, the tilde-prefix
 * is replaced with the home directory associated with the
 * specified login name.
 *
 */

#ifndef FORBIDDEN_FUNCTIONS

int	ft_sethome(t_data *data)
{
	bool	need2free;
	char	*home;

	need2free = false;
	home = ft_getenv("HOME", (const char **) data->envp);
	if (home == NULL)
	{
		home = getenv("HOME");
		if (home == NULL)
		{
			home = ft_gethome_fstab();
			if (home == NULL)
				home = "hey";
			need2free = true;
		}
	}
	data->home = ft_strdup(home);
	if (need2free == true)
		free(home);
	return (EXIT_SUCCESS);
}

#else /* FORBIDDEN_FUNCTIONS is defined */

int	ft_sethome(t_data *data)
{
	char	*home;

	home = ft_getenv("HOME", (const char **) data->envp);
	if (home == NULL)
	{
		home = getlogin();
		ft_setenv("HOME", home, 1, &data->envp);
	}
	return (EXIT_SUCCESS);
}

#endif

static char	*ft_gethome_fstab(void)
{
	int		file;
	char	*home;
	char	*line;
	char	*prev_line;
	char	**split;

	prev_line = NULL;
	file = open(_PATH_FSTAB, O_RDONLY);
	if (file == -1)
		return (NULL);
	line = get_next_line(file);
	while (line != NULL)
	{
		prev_line = line;
		line = get_next_line(file);
		if (line == NULL)
			break ;
		free(prev_line);
	}
	close(file);
	split = ft_split(prev_line, ' ');
	free(prev_line);
	home = ft_strdup(split[1]);
	return (ft_free_str_arr(split), home);
}
