/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 11:58:13 by framos-p          #+#    #+#             */
/*   Updated: 2023/06/28 12:23:20 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"

static int	change_to_parent_directory(const char *directory, t_data *data)
{
	char		cwd[PATH_MAX];
	const char	*prev_dir;

	prev_dir = ft_getenv("PWD", (const char **)data->envp);
	printf("antes: %s\n", prev_dir);
	if (access("..", R_OK) == -1)
	{
		ft_error(NO_PERMIT, "..");
		chdir(directory);
	}
	if (chdir("..") == 0)
	{
		if (getcwd(cwd, PATH_MAX) != NULL)
			ft_setenv("PWD", cwd, 1, &data->envp);
		printf("en medio: %s\n", prev_dir);
		if (ft_setenv("OLDPWD", prev_dir, 1, &data->envp) != 0)
			return (ft_error(ERR_OPWD, directory), EXIT_FAILURE);
		printf("despues: %s\n", prev_dir);
	}
	else if (getcwd(cwd, PATH_MAX) != NULL)
		ft_setenv("PWD", cwd, 1, &data->envp);
	return (EXIT_SUCCESS);
}

static int	change_to_home_directory(const char *directory, t_data *data)
{
	char		path[PATH_MAX];
	const char	*home_dir;
	const char	*prev_dir;

	prev_dir = ft_getenv("PWD", (const char **)data->envp);
//	printf("%s\n", prev_dir);
	home_dir = ft_getenv("HOME", (const char **)data->envp);
	if (!home_dir)
		return (ft_error(NO_HOME, directory), EXIT_FAILURE);
	if (access(home_dir, R_OK) != 0)
		return (ft_error(NO_PERMIT, directory), EXIT_FAILURE);
	if (chdir(home_dir) != 0)
		return (ft_error(NO_HOME, directory), EXIT_FAILURE);
	if (ft_setenv("OLDPWD", prev_dir, 1, &data->envp) != 0)
		return (ft_error(ERR_PWD, directory), EXIT_FAILURE);
	if (getcwd(path, sizeof(path)) == NULL)
		return (ft_error(ERR_CD, directory), EXIT_FAILURE);
	if (ft_setenv("PWD", path, 1, &data->envp) != 0)
		return (ft_error(ERR_PWD, directory), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	change_to_previous_directory(t_data *data)
{
	char		cwd[PATH_MAX];
	const char	*prev_dir;
	char		current_dir[PATH_MAX];

	prev_dir = ft_getenv("OLDPWD", (const char **)data->envp);
//	printf("%s\n", prev_dir);
	if (!prev_dir || chdir(prev_dir) != 0)
	{
		printf("cd: no such file or directory: %s\n", prev_dir);
		return (EXIT_FAILURE);
	}
//	printf("%s\n", prev_dir);
	if (!getcwd(current_dir, sizeof(current_dir)))
	{
		printf("minishell: cd: %s: No such file or directory\n", current_dir);
		return (EXIT_FAILURE);
	}
	if (ft_setenv("OLDPWD", prev_dir, 1, &data->envp) != 0)
	{
		printf("Failed to set OLDPWD\n");
		return (EXIT_FAILURE);
	}
//	printf("%s\n", prev_dir);
	if (getcwd(cwd, PATH_MAX) == NULL || ft_setenv("PWD", cwd, 1, &data->envp) != 0)
	{
		printf("Failed to set PWD\n");
		return (EXIT_FAILURE);
	}
//	printf("%s\n", current_dir);
//	printf("%s\n", prev_dir);
	return (EXIT_SUCCESS);
}

static int	change_to_directory(const char *directory, t_data *data)
{
	char			cwd[PATH_MAX];
	struct stat		dir_stat;

	if (directory == NULL || directory[0] == '\0')
		return (EXIT_SUCCESS);
	if (stat(directory, &dir_stat) == 0)
	{
		if (S_ISDIR(dir_stat.st_mode))
		{
			if (chdir(directory) == 0)
			{
				if (getcwd(cwd, PATH_MAX) != NULL)
					return (ft_setenv("PWD", cwd, 1, &data->envp), EXIT_SUCCESS);
			}
			else
				return (ft_error(NO_PERMIT, directory), EXIT_FAILURE);
		}
		else
			return (ft_error(NO_DIR, directory), EXIT_FAILURE);
	}
	else if (access(directory, F_OK) == -1)
		return (ft_error(NO_SUCH_DIR, directory), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_cd(t_cmd *cmd, t_data *data)
{
	int	i;

	i = -1;
	cmd->tokens_count = 0;
	while (cmd->tokens[++i] != NULL)
		cmd->tokens_count++;
	if (cmd->tokens_count - 1 > 2)
		return (ft_fprintf(stderr, "minishell: %s No such file or directory\n",
				cmd->tokens[0]), EXIT_FAILURE);
	if (cmd->tokens[1] == NULL || cmd->tokens[1][0] == '\0'
		|| ft_strncmp(cmd->tokens[1], "~", 1) == 0)
		return (change_to_home_directory(cmd->tokens[1], data), EXIT_SUCCESS);
	else if (ft_strncmp(cmd->tokens[1], "..", 2) == 0)
		return (change_to_parent_directory(cmd->tokens[1],data), EXIT_SUCCESS);
	else if (ft_strncmp(cmd->tokens[1], "-", 1) == 0)
		return (change_to_previous_directory(data), EXIT_SUCCESS);
	else
		return (change_to_directory(cmd->tokens[1], data), EXIT_SUCCESS);
	return (EXIT_FAILURE);
}
