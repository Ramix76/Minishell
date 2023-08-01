/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _minishell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:36:58 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/08/01 12:06:34 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _MINISHELL_H
# define _MINISHELL_H

typedef struct s_data
{
	int		exit_code;
	int		in;
	int		out;
	char	*path;
	char	*home;
	char	*exec_dir;
	char	**envp;
	char	**exported_vars;
}			t_data;

typedef struct s_cmd
{
	char	*command;
	char	**tokens;
	int		tokens_count;
}			t_cmd;

#endif /* _minishell.h */
