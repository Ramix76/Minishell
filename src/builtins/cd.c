/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 11:58:13 by framos-p          #+#    #+#             */
/*   Updated: 2023/06/08 15:13:14 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"

static void	changeToParentDirectory()
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

static void	changeToHomeDirectory()
{
	char		path[PATH_MAX];
	const char	*home_dir;

	home_dir = getenv("HOME");
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

static void	changeToPreviousDirectory()
{
	char		path[PATH_MAX];
	const char	*prev_dir;

	prev_dir = getenv("OLDPWD");
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

static void	changeToDirectory(const char *directory)
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
	char	path[PATH_MAX];

	if (argc != 2)
	{
		printf("Use: %s <directory's name>\n", argv[0]);
		return (EXIT_FAILURE);
	}
	if (strcmp(argv[1], "..") == 0)
		changeToParentDirectory();
	else if (strcmp(argv[1], "~") == 0)
		changeToHomeDirectory();
	else if (strcmp(argv[1], "-") == 0)
		changeToPreviousDirectory();
	else
		changeToDirectory(argv[1]);
	if (getcwd(path, sizeof(path)) != NULL)
		printf("Current directory: %s\n", path);
	return (EXIT_SUCCESS);
}
