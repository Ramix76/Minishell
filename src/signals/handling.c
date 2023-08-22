/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 15:08:16 by framos-p          #+#    #+#             */
/*   Updated: 2023/08/22 14:45:27 by framos-p         ###   ########.fr       */
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
	}
	else if (signal == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		g_exit_code = 130;
	}
}

static void	ft_sig_handler_heredoc(int signal)
{
	if (signal == SIGINT)
	{
		g_exit_code = 130;
		write(STDOUT_FILENO, "\n", 1);
		exit(g_exit_code);
	}
}

void	ft_do_sigign(int signal)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_IGN;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	if (sigaction(signal, &sa, NULL) < 0)
		exit(1);
}

int	ft_init_signals(int mode)
{
	struct sigaction	sa;

	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	if (mode == 0)
		sa.sa_handler = &ft_sig_handler_normal;
	else if (mode == 1)
		sa.sa_handler = &ft_sig_handler_interact;
	else if (mode == 2)
		sa.sa_handler = &ft_sig_handler_heredoc;
	else if (mode == 3)
		sa.sa_handler = ft_do_sigign;
	sigaction(SIGINT, &sa, NULL);
	if (!mode)
	{
		sa.sa_handler = SIG_IGN;
		sa.sa_flags = SA_RESTART;
		sigemptyset(&sa.sa_mask);
		sigaction(SIGQUIT, &sa, NULL);
	}
	sigaction(SIGQUIT, &sa, NULL);
	return (EXIT_SUCCESS);
}
