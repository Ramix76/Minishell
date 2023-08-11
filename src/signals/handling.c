/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 15:08:16 by framos-p          #+#    #+#             */
/*   Updated: 2023/08/11 12:25:08 by mpuig-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_signal_handler(int signal);
//static void	ft_handle_signals_heredoc(int signal);

static void	ft_signal_handler(int signal)
{
	if (signal == SIGQUIT)
	{
		rl_redisplay();
		return ;
	}
	else if (signal == SIGINT)
	{
		if (g_in_heredoc == 1)
		{
			rl_on_new_line();
			write(STDOUT_FILENO, "\n", 1);
			g_in_heredoc = 0;
		}
		else if (g_in_heredoc == 0)
		{
			rl_on_new_line();
			write(STDOUT_FILENO, "\n", 1);
			rl_redisplay();
		}
	}
}

/*static void	ft_handle_signals_heredoc(int signal)
{
	if (signal == SIGQUIT)
		return ;
	else if (signal == SIGINT)
	{
		if (g_in_heredoc == 1)
		{
			printf("Hey\n");
			close(STDIN_FILENO);
			write(STDOUT_FILENO, "> ^C", 5);
			g_in_heredoc = 0;
		}
	}
}*/

int	ft_init_signals(int mode, t_data *data)
{
	struct sigaction	sa;

	(void)data;
	data->running = 1;
	sa.sa_flags = SA_SIGINFO;
	if (mode == 1)
		sa.sa_handler = SIG_IGN;
	else if (mode == 2)
		sa.sa_handler = &ft_signal_handler;
	else if (mode == 3)
		sa.sa_handler = &ft_signal_handler;
	else if (mode == 0)
		sa.sa_handler = SIG_DFL;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	return (EXIT_SUCCESS);
}
