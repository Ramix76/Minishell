/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _minishell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:36:58 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/07/12 12:09:54 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _MINISHELL_H
# define _MINISHELL_H

typedef struct s_data
{
	char	*path;
	char	**envp;
	int		exit_code;
	char	**exported_vars;
}			t_data;

typedef struct s_cmd
{
	char	*command;
	char	**tokens;
	int		tokens_count;
}			t_cmd;

#endif /* _minishell.h */
