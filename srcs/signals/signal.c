/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brturcio <brturcio@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 10:32:34 by brturcio          #+#    #+#             */
/*   Updated: 2025/06/12 06:26:00 by brturcio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_sigint_handler(int signal)
{
	(void)signal;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	ft_handler_heredoc(int signal)
{
	(void)signal;
	write(1, "^C", 2);
	write(1, "\n", 1); // Para mostrar nueva línea como bash
	exit(130); // Código estándar para Ctrl+C
}


/**
 * @brief Waits for all child processes and sets the appropriate exit status.
 *
 * For each child process:
 * - If terminated by signal, sets `exit_status = 128 + signal`.
 * - If terminated normally, sets `exit_status = exit code`.
 * - Prints "Quit (core dumped)" if the child received SIGQUIT.
 *
 * This ensures `$?` behaves like in bash.
 *
 * @param shell The shell state structure.
 */
// void	ft_wait_and_set_exit_status(t_shell *shell)
// {
// 	int	i;
// 	int	status;
// 	int	sig;

// 	i = 0;
// 	while (i < shell->nb_cmds)
// 	{
// 		if (shell->pids[i] > 0)
// 		{
// 			waitpid(shell->pids[i], &status, 0);
// 			if (WIFSIGNALED(status))
// 			{
// 				sig = WTERMSIG(status);
// 				shell->exit_status = 128 + sig;
// 				if (sig == SIGQUIT)
// 					ft_putendl_fd("Quit (core dumped)", STDOUT_FILENO);
// 				// if (sig == SIGINT && g_signal != MAIN_SIGINT)
// 				// 	write(STDOUT_FILENO, "\n", 1);
// 			}
// 			else if (WIFEXITED(status))
// 				shell->exit_status = WEXITSTATUS(status);
// 		}
// 		i++;
// 	}
// }

void	ft_wait_and_set_exit_status(t_shell *shell)
{
	int	i;
	int	status;
	int	sig;
	int	first_signal; // Variable para imprimir solo una nueva línea

	i = 0;
	first_signal = 1;

	// 1. ANTES de esperar, el padre se configura para IGNORAR las señales.
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);

	while (i < shell->nb_cmds)
	{
		if (shell->pids[i] > 0)
		{
			waitpid(shell->pids[i], &status, 0);
			if (WIFSIGNALED(status))
			{
				sig = WTERMSIG(status);
				shell->exit_status = 128 + sig;
				if (sig == SIGQUIT && first_signal)
				{
					ft_putendl_fd("Quit", STDOUT_FILENO);
					first_signal = 0;
				}
				if (sig == SIGINT && first_signal)
				{
					write(STDOUT_FILENO, "\n", 1);
					first_signal = 0;
				}
			}
			else if (WIFEXITED(status))
				shell->exit_status = WEXITSTATUS(status);
		}
		i++;
	}

	// 2. DESPUÉS de esperar, el padre restaura los manejadores interactivos.

}


void	ft_update_exit_status_by_signal(t_shell *shell)
{
	(void)shell;
	// if (g_signal == MAIN_SIGINT || g_signal == HEREDOC_SIGINT)
	// 	shell->exit_status = 130;
	// else if (g_signal == EXEC_SIGQUIT)
	// 	shell->exit_status = 131;
	// g_signal = NO_SIGNAL;
}
