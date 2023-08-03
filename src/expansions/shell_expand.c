/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:45:44 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/08/03 13:02:38 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_expand_token(char *str, t_data *data);

int	ft_shell_expand(char **tokens, t_data *data)
{
	int		i;
	char	*token;

	i = 0;
	while (tokens != NULL && tokens[i] != NULL)
	{
		token = tokens[i];
		tokens[i] = ft_expand_token(token, data);
		printf("t: %s\n", tokens[i]);
		free(token);
		++i;
	}
	return (EXIT_SUCCESS);
}

static char	*ft_expand_token(char *str, t_data *data)
{
	char	*temp;
	char	*expanded;

	expanded = ft_strdup(str);
	temp = expanded;
	expanded = ft_expand_tilde(expanded, data);
	free(temp);
	temp = expanded;
	expanded = ft_expand_dollar(expanded, data);
	free(temp);	
	temp = expanded;
	expanded = ft_expand_quotes(expanded);
	free(temp);
	return (expanded);
}
