/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _minishell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:36:58 by mpuig-ma          #+#    #+#             */
/*   Updated: 2023/08/10 14:30:45 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _MINISHELL_H
# define _MINISHELL_H

typedef struct s_data
{
	int		exit_code;
	int		fd;
	int		in;
	int		out;
	int		pipe;
	int		running;
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
