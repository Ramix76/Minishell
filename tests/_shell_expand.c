/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: m███████ <m███████@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:45:44 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/06/14 19:15:52 by mpuig-ma         ###   ########.fr       */
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
	new_envp = (char **) malloc(sizeof(char *) * (len + 1));
	if (new_envp == NULL)
		return (EXIT_FAILURE);
	while (len-- > 0)
		new_envp[len] = ft_strdup(envp[len]);
	new_envp[len] = NULL;
	data->envp = new_envp;
	return (EXIT_SUCCESS);
}

static int	init_data(int argc, char **argv, char **envp, t_data *data)
{
	(void) argc;
	(void) argv;
	init_env(envp, data);
	data->path = ft_getenv("PATH", (const char **) envp);
	if (data->path == NULL)
		data->path = _PATH_DEFPATH;
	data->exit_code = 0;
	return (EXIT_SUCCESS);
}

static void	print_str_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
		ft_printf("%s\n", arr[i++]);
}

static char	*parameter_expansion(char *str, t_data *data);

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	str[] = "visca \"barsa\" $HEY, $?$$";

	init_log(argc, argv, envp);
	init_data(argc, argv, envp, &data);
	ft_printf("%s\n", shell_expand(str, &data));
	return (0);
}

char	*shell_expand(char *str, t_data *data)
{
	char	*expanded;

	expanded = str;
	expanded = parameter_expansion(str, data);
	return (expanded);
}

static char	*parameter_expansion(char *str, t_data *data)
{
	size_t	str_len;
	char	*expanded;
	char	*temp;

	(void) data;
	(void) print_str_arr;
	str_len = ft_strlen(str);
	temp = str;
	while (temp && *temp != '\0')
	{
		if (*temp != '$')
			ft_printf("%c\n", *temp);
		else
		{
			ft_printf("stuff\n");
			++temp;
			while (temp && *temp != '\0' && *temp != '$' && ft_isspace(*temp) == 0)
				temp++;
		}
		temp++;
	}
	/*
	temp = ft_strchr(str, '$');
	if (temp == NULL)
		return (str);
	while (temp != NULL)
	{
		ft_printf("$ + %c\n", *(temp + 1));
		temp = ft_strchr(temp + 1, '$');
	}
	*/
	(void) temp;
	expanded = str;
	return (expanded);
}
