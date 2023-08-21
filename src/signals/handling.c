/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 15:08:16 by framos-p          #+#    #+#             */
/*   Updated: 2023/08/21 16:28:02 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_sig_handler_normal(int signal);
static void	ft_sig_handler_interact(int signal);
static void	ft_sig_handler_heredoc(int signal);

static void	ft_sig_handler_normal(int signal)
{
	if (signal == SIGINT)
	{
		g_exit_code = 130;
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

static void	ft_sig_handler_interact(int signal)
{
	if (signal == SIGQUIT)
	{
		printf("Quit: 3\n");
		g_exit_code = 131;
		return ;
	}
	else if (signal == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		g_exit_code = 130;
	}
}

static void	ft_sig_handler_heredoc(int signal)
{
	if (signal == SIGQUIT)
		return ;
	else if (signal == SIGINT)
	{
		close(STDIN_FILENO);
		write(STDOUT_FILENO, "> ^C", 5);
		g_exit_code = 130;
	}
}

int	ft_init_signals(int mode, t_data *data)
{
	struct sigaction	sa;

	(void)data;
	data->running = 1;
	sa.sa_flags = SA_SIGINFO;
	if (mode == 0)
		sa.sa_handler = &ft_sig_handler_normal;
	else if (mode == 1)
		sa.sa_handler = &ft_sig_handler_interact;
	else if (mode == 2)
		sa.sa_handler = &ft_sig_handler_heredoc;
	sigaction(SIGINT, &sa, NULL);
	if (!mode)
	{
		sa.sa_handler = SIG_IGN;
		sigaction(SIGQUIT, &sa, NULL);
	}
	else
		sigaction(SIGQUIT, &sa, NULL);
	return (EXIT_SUCCESS);
}
