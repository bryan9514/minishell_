/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brturcio <brturcio@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 17:23:25 by yel-mens          #+#    #+#             */
/*   Updated: 2025/07/01 15:13:09 by brturcio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_shell_and_token(t_shell *shell, int exit_status)
{
	t_token	*token;

	token = shell->tokens;
	while (token)
	{
		if (token->in > 0)
		{
			close(token->in);
			token->in = -1;
		}
		token = token->next;
	}
	ft_free_shell(shell);
	exit(exit_status);
}

int	ft_limiter_check(char *limiter)
{
	int	shift;
	int	i;

	shift = 0;
	i = 0;
	while (limiter[i])
	{
		if (limiter[i] == '"' || limiter[i] == '\'')
			shift++;
		else
			limiter[i - shift] = limiter[i];
		i++;
	}
	limiter[i - shift] = 0;
	if (shift > 0)
		return (0);
	return (1);
}

void	ft_heredoc_exit(char *line, int end[2], t_shell *shl)
{
	free(line);
	close(end[1]);
	ft_free_shell_and_token(shl, EXIT_SUCCESS);
}

int	ft_heredoc_continuation(t_shell *shell, pid_t pid, \
struct termios *original_config, int *end)
{
	int	status;

	(void) shell;
	close(end[1]);
	ft_signals_ign();
	waitpid(pid, &status, 0);
	tcsetattr(STDIN_FILENO, TCSANOW, original_config);
	ft_control_signals_main();
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
	{
		g_signal = MAIN_SIGINT;
		close(end[0]);
	}
	else if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_FAILURE)
		ft_printf("\nminishell: warning: here-document delimited "\
"by end-of-file (wanted 'delimiter')\n");
	return (status);
}

void	ft_heredoc(char *limiter, t_token *tk, t_shell *shell)
{
	pid_t			pid;
	int				end[2];
	struct termios	original_config;
	struct termios	heredoc_config;
	int				status;

	tcgetattr(STDIN_FILENO, &original_config);
	heredoc_config = original_config;
	heredoc_config.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &heredoc_config);
	if (pipe(end) < 0)
		ft_error("Cannot open pipe in heredoc", EXIT_FD, shell);
	pid = fork();
	if (pid < 0)
		ft_error("fork in heredoc failed", EXIT_FD, shell);
	if (pid == 0)
	{
		close(end[0]);
		ft_control_signals_heredoc();
		ft_read_stdin(end, limiter, shell);
		exit(EXIT_SUCCESS);
	}
	status = ft_heredoc_continuation(shell, pid, &original_config, end);
	if (!(WIFEXITED(status) && WEXITSTATUS(status) == 130))
		tk->in = end[0];
}
