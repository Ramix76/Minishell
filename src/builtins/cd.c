/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 11:58:13 by framos-p          #+#    #+#             */
/*   Updated: 2023/06/08 16:43:17 by framos-p         ###   ########.fr       */
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
			printf("New current directory: %s\n", path);
		else
			perror("No such file or directory\n");
	}
	else
		perror("No such file or directory\n");
}

static void	change_to_home_directory(t_data *data)
{
	char		path[PATH_MAX];
	const char	*home_dir;

	home_dir = ft_getenv("HOME", (const char **)data->envp);
	if (home_dir == NULL)
		perror("Error obtaining HOME directory\n");
	if (chdir(home_dir) == 0)
	{
		if (getcwd(path, sizeof(path)) != NULL)
			printf("New current directory: %s\n", path);
		else
			perror("HOME not set\n");
	}
	else
		perror("Error changing directory\n");
}

static void	change_to_previous_directory(t_data *data)
{
	char		path[PATH_MAX];
	const char	*prev_dir;

	prev_dir = ft_getenv("OLDPWD", (const char **)data->envp);
	if (prev_dir == NULL)
		perror("Error obtaining previous directory\n");
	if (chdir(prev_dir) == 0)
	{
		if (getcwd(path, sizeof(path)) != NULL)
			printf("New current directory: %s\n", path);
		else
			perror("Error obtaining new route\n");
	}
	else
		perror("Error changing dirctory\n");
}

static void	change_to_directory(const char *directory)
{
	char	path[PATH_MAX];

	if (chdir(directory) == 0)
	{
		if (getcwd(path, sizeof(path)) != NULL)
			printf("New current directory: %s\n", path);
		else
			perror("No such file or directory\n");
	}
	else
		perror("Error changing directory\n");
}

int	ft_cd(t_cmd *cmd, t_data *data)
{
	(void)data;
	int	i;

	i = 0;
	cmd->tokens_count = 0;
	while(cmd->tokens[i] != NULL)
	{
		cmd->tokens_count++;
		i++;
	}
	if (cmd->tokens_count - 1 != 1)
	{
		printf("Use: %s <directory's name>\n", cmd->tokens[0]);
		return (EXIT_FAILURE);
	}
	if (ft_strncmp(cmd->tokens[1], "..", 2) == 0)
		change_to_parent_directory();
	else if (ft_strncmp(cmd->tokens[1], "~", 1) == 0)
		change_to_home_directory(data);
	else if (ft_strncmp(cmd->tokens[1], "-", 1) == 0)
		change_to_previous_directory(data);
	else
		change_to_directory(cmd->tokens[1]);
	return (EXIT_SUCCESS);
}
