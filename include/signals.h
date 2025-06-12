/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brturcio <brturcio@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 10:44:05 by brturcio          #+#    #+#             */
/*   Updated: 2025/06/06 16:48:23 by brturcio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "minishell.h"

typedef enum e_context
{
	NO_SIGNAL,
	MAIN_SIGINT,
	HEREDOC_SIGINT,
	HEREDOC_INTERRUPTED,
	EXEC_SIGINT,
	EXEC_SIGQUIT
}		t_context;

void	ft_control_signals_main(void);
void	ft_control_signals_child(void);
void	ft_control_signals_heredoc(void);

void	ft_sigint_handler(int signal);
void	ft_handler_heredoc(int signal);
void	ft_wait_and_set_exit_status(t_shell *shell);
void	ft_update_exit_status_by_signal(t_shell *shell);

#endif
