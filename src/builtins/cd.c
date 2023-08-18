/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 11:58:13 by framos-p          #+#    #+#             */
/*   Updated: 2023/08/18 14:19:09 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_change_to_parent_directory(const char *dir, t_data *data);
static int	ft_change_to_home_directory(const char *dir, t_data *data);
static int	ft_change_to_previous_directory(t_data *data);
static int	ft_change_to_directory(const char *dir, t_data *data);
int			ft_cd_ultra_specific_situation(void);

static int	ft_change_to_parent_directory(const char *dir, t_data *data)
{
	char		cwd[PATH_MAX];
	char		prev_dir[PATH_MAX];

	if (access("..", R_OK) == -1)
	{
		chdir(dir);
		ft_error("cd", "..");
		return ((data->exit_code = 1), EXIT_FAILURE);
	}
	if (getcwd(prev_dir, PATH_MAX) == NULL)
		return (ft_fprintf(stderr, "%s: cd: ..: No such file or directory\n",
				SH_NAME, (data->exit_code = 1), EXIT_FAILURE));
	if (chdir("..") == 0)
	{
		if (getcwd(cwd, PATH_MAX) != NULL)
			ft_setenv("PWD", cwd, 1, &data->envp);
		if (ft_setenv("OLDPWD", prev_dir, 1, &data->envp) != 0)
			return (ft_fprintf(stderr, "%s: cd: Failed to set PWD\n", SH_NAME),
				(data->exit_code = 1), EXIT_FAILURE);
	}
	else if (getcwd(cwd, PATH_MAX) != NULL)
		ft_setenv("PWD", cwd, 1, &data->envp);
	return ((data->exit_code = 0), EXIT_SUCCESS);
}

static int	ft_change_to_home_directory(const char *dir, t_data *data)
{
	char		path[PATH_MAX];
	char		*home_dir;
	char		prev_dir[PATH_MAX];

	home_dir = ft_getenv("HOME", (const char **)data->envp);
	if (getcwd(prev_dir, PATH_MAX) == NULL)
		return ((data->exit_code = 1), EXIT_FAILURE);
	if (access(home_dir, R_OK) != 0 || chdir(home_dir) != 0)
		return (ft_error("cd", dir), (data->exit_code = 1), EXIT_FAILURE);
	if (ft_setenv("OLDPWD", prev_dir, 1, &data->envp) != 0)
		return (ft_fprintf(stderr, "%s: cd: OLDPWD not set\n", SH_NAME),
			(data->exit_code = 1), EXIT_FAILURE);
	if (getcwd(path, PATH_MAX) == NULL)
		return (ft_fprintf(stderr, "%s: cd: Failed to get current directory\n",
				SH_NAME), (data->exit_code = 1), EXIT_FAILURE);
	if (ft_setenv("PWD", path, 1, &data->envp) != 0)
		return (ft_fprintf(stderr, "%s: cd: OLDPWD not set\n", SH_NAME),
			(data->exit_code = 1), EXIT_FAILURE);
	return ((data->exit_code = 0), EXIT_SUCCESS);
}

static int	ft_change_to_previous_directory(t_data *data)
{
	char		cwd[PATH_MAX];
	const char	*prev_dir;
	char		current_dir[PATH_MAX];

	prev_dir = ft_getenv("OLDPWD", (const char **)data->envp);
	if (!prev_dir)
		return (ft_fprintf(stderr, "%s: cd: OLDPWD not set\n", SH_NAME),
			(data->exit_code = 1), EXIT_FAILURE);
	if (!getcwd(current_dir, sizeof(current_dir)))
		return (ft_error(current_dir, prev_dir), ENOENT);
	if (chdir(prev_dir) != 0)
		return (ft_error("cd", prev_dir), (data->exit_code = 1), EXIT_FAILURE);
	if (getcwd(cwd, PATH_MAX) == NULL)
		return (ft_fprintf(stderr, "%s: cd: Failed to get current directory\n",
				SH_NAME), (data->exit_code = 1), EXIT_FAILURE);
	if (ft_setenv("PWD", cwd, 1, &data->envp) != 0)
		return (ft_fprintf(stderr, "%s: cd: PWD not set\n", SH_NAME),
			(data->exit_code = 1), EXIT_FAILURE);
	if (ft_setenv("OLDPWD", current_dir, 1, &data->envp) != 0)
		return (ft_fprintf(stderr, "%s: cd: OLDPWD not set\n", SH_NAME),
			(data->exit_code = 1), EXIT_FAILURE);
	return ((data->exit_code = 0), EXIT_SUCCESS);
}

static int	ft_change_to_directory(const char *dir, t_data *data)
{
	char			cwd[PATH_MAX];
	struct stat		dir_stat;

	if (dir == NULL || dir[0] == '\0')
		return ((data->exit_code = 0), EXIT_SUCCESS);
	if (getcwd(cwd, PATH_MAX) == NULL)
		return (ft_cd_ultra_specific_situation());
	if (stat(dir, &dir_stat) == 0)
	{
		if (S_ISDIR(dir_stat.st_mode))
		{
			if (chdir(dir) == 0 && getcwd(cwd, PATH_MAX) != NULL)
				return (ft_setenv("PWD", cwd, 1, &data->envp), 0);
			else
				return (ft_error("cd", dir), (data->exit_code = 1),
					EXIT_FAILURE);
		}
		else
			return (ft_fprintf(stderr, "%s: cd: %s: Not a directory\n",
					SH_NAME, dir), (data->exit_code = 1), EXIT_FAILURE);
	}
	else if (access(dir, F_OK) == -1)
		return (ft_error("cd", dir), (data->exit_code = 1), EXIT_FAILURE);
	return ((data->exit_code = 0), EXIT_SUCCESS);
}

int	ft_cd(t_cmd *cmd, t_data *data)
{
	if (ft_cd_check_arguments(cmd) == EXIT_FAILURE)
		return ((data->exit_code = 1), EXIT_FAILURE);
	if (ft_strcmp("--", cmd->tokens[1]) == 0)
	{
		free(cmd->tokens[1]);
		if (cmd->tokens[2] != NULL)
			cmd->tokens[1] = ft_strdup(cmd->tokens[2]);
		else
			cmd->tokens[1] = NULL;
	}
	if (cmd->tokens[1] == NULL)
	{
		if (ft_getenv("HOME", (const char **)data->envp) == NULL)
			return (ft_fprintf(stderr, "%s: cd: HOME not set\n", SH_NAME),
				(data->exit_code = 1), EXIT_FAILURE);
		return (ft_change_to_home_directory(cmd->tokens[1], data),
			(data->exit_code = 0), EXIT_SUCCESS);
	}
	else if (ft_strncmp(cmd->tokens[1], "..", 2) == 0)
		return (ft_change_to_parent_directory(cmd->tokens[1], data),
			(data->exit_code = 0), EXIT_SUCCESS);
	else if (ft_strcmp("-", cmd->tokens[1]) == 0)
		return (ft_change_to_previous_directory(data),
			(data->exit_code = 0), EXIT_SUCCESS);
	return (ft_change_to_directory(cmd->tokens[1], data));
}
