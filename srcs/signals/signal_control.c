/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brturcio <brturcio@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:12:14 by brturcio          #+#    #+#             */
/*   Updated: 2025/06/10 19:57:08 by brturcio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_control_signals_main(void)
{	g_signal = MAIN_SIGINT;
	signal(SIGINT, ft_sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
void	ft_control_signals_child(void)
{
	g_signal = EXEC_SIGINT;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGPIPE, SIG_IGN);
}
void	ft_control_signals_heredoc(void)
{
	g_signal = HEREDOC_SIGINT;
	signal(SIGINT, ft_handler_heredoc);
	signal(SIGQUIT, SIG_IGN);
}

