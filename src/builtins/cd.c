/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 11:58:13 by framos-p          #+#    #+#             */
/*   Updated: 2023/06/13 13:29:53 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"

static void	change_to_parent_directory(void)
{
	char	path[PATH_MAX];

	if (chdir("..") == 0)
	{
		if (getcwd(path, sizeof(path)) != NULL)
			return ;
		else
			printf("No such file or directory\n");
	}
	else
		perror("No such file or directory\n");
}

static int	change_to_home_directory(t_cmd *cmd, t_data *data)
{
	char		path[PATH_MAX];
	const char	*home_dir;

	home_dir = ft_getenv("HOME", (const char **)data->envp);
	if (!home_dir)
	{
		printf("Error obtaining HOME directory\n");
		return (EXIT_FAILURE);
	}
	if (chdir(home_dir) != 0)
	{
		if (cmd->tokens[1] == NULL)
			printf("minishell: cd: HOME not set\n");
		return (EXIT_FAILURE);
	}
	if (!getcwd(path, sizeof(path)))
	{
		printf("HOME not set\n");
		return (EXIT_FAILURE);
	}
	if (setenv("PWD", path, 1) != 0)
	{
		printf("Failed to set PWD\n");
		return (EXIT_FAILURE);
	}
	printf("HOME set to: %s\n", path);
	return (EXIT_SUCCESS);
}

static int	change_to_previous_directory(t_data *data)
{
	char		path[PATH_MAX];
	const char	*prev_dir;
	char		current_dir[PATH_MAX];

	prev_dir = ft_getenv("OLDPWD", (const char **)data->envp);
	if (!prev_dir || chdir(prev_dir) != 0)
	{
		printf("cd: no such file or directory: %s\n", prev_dir);
		return (EXIT_FAILURE);
	}
	if (!getcwd(current_dir, sizeof(current_dir)))
	{
		printf("minishell: cd: %s: No such file or directory\n", current_dir);
		return (EXIT_FAILURE);
	}
	if (setenv("OLDPWD", current_dir, 1) != 0)
	{
		printf("Failed to set OLDPWD\n");
		return (EXIT_FAILURE);
	}
	if (getcwd(path, sizeof(path)) == NULL || setenv("PWD", path, 1) != 0)
	{
		printf("Failed to set PWD\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	change_to_directory(const char *directory)
{
	char	path[PATH_MAX];

	if (chdir(directory) == 0)
	{
		if (getcwd(path, sizeof(path)) != NULL)
			return (EXIT_SUCCESS);
	}
	else if (access(directory, F_OK) == -1)
	{
		printf("miinishell: cd: %s: No such file or directory\n", directory);
		return (EXIT_FAILURE);
	}
	else
	{
		if (access(directory, R_OK | X_OK) == -1)
		{
			printf("cd: Permission denied: %s\n", directory);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

int	ft_cd(t_cmd *cmd, t_data *data)
{
	int	i;

	i = 0;
	cmd->tokens_count = 0;
	while (cmd->tokens[i] != NULL)
	{
		cmd->tokens_count++;
		i++;
	}
	if (cmd->tokens_count - 1 > 2)
	{
		printf("Use: %s <directory's name>\n", cmd->tokens[0]);
		return (EXIT_FAILURE);
	}
	if (cmd->tokens[1] == NULL
		|| (ft_strncmp(cmd->tokens[1], "~", 1) == 0))
		change_to_home_directory(cmd, data);
	else if (ft_strncmp(cmd->tokens[1], "..", 2) == 0)
		change_to_parent_directory();
	else if (ft_strncmp(cmd->tokens[1], "-", 1) == 0)
		change_to_previous_directory(data);
	else
		change_to_directory(cmd->tokens[1]);
	return (EXIT_SUCCESS);
}
