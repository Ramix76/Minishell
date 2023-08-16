/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 11:36:55 by framos-p          #+#    #+#             */
/*   Updated: 2023/08/16 14:41:34 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int			ft_is_numeric_argument(char *str);
static long long	ft_atoll(const char *str);

int	ft_exit(t_cmd *cmd, t_data *data)
{
	size_t		len;

	len = ft_arrlen(cmd->tokens);
	if (isatty(STDIN_FILENO))
		ft_fprintf(stderr, "exit\n");
	if (len > 1 && !ft_is_numeric_argument(cmd->tokens[1]))
	{
		ft_fprintf(stderr, "%s: exit: %s: numeric argument required\n",
			SH_NAME, cmd->tokens[1]);
		return ((data->running = 0), (data->exit_code = 2), EXIT_FAILURE);
	}
	if (len > 2)
	{
		ft_fprintf(stderr, "%s: exit: too many arguments\n", SH_NAME);
		return ((data->exit_code = 1), EXIT_FAILURE);
	}
	if (len > 1)
		data->exit_code = (unsigned char)ft_atoll(cmd->tokens[1]);
	return ((data->running = 0), EXIT_SUCCESS);
}

static int	ft_is_numeric_argument(char *str)
{
	char	*temp;

	temp = ft_strtrim(str, " ");
	str = temp;
	while (*str == '0' && *(str + 1) != '\0')
		str++;
	if (ft_strlen(str) > ft_strlen("-9223372036854775808")
		|| (ft_strlen(str) == ft_strlen("-9223372036854775807")
			&& ft_strncmp(str, "-9223372036854775808", ft_strlen(str)) > 0))
		return (0);
	else if (ft_strlen(str) == ft_strlen("9223372036854775807")
		&& ft_strncmp(str, "9223372036854775807", ft_strlen(str)) > 0)
		return (0);
	if (*str == '-' || *str == '+')
		str++;
	if (*str == '\0')
		return (0);
	while (*str != '\0')
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	free(temp);
	return (1);
}

static long long	ft_atoll(const char *str)
{
	long long	result;
	int			sign;
	int			i;

	result = 0;
	sign = 1;
	i = 0;
	if (ft_strncmp(str, "-9223372036854775808", ft_strlen(str)) == 0)
		return (0);
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (isdigit(str[i]))
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}
