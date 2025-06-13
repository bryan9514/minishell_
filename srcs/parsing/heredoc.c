/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brturcio <brturcio@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 17:23:25 by yel-mens          #+#    #+#             */
/*   Updated: 2025/06/13 07:12:41 by brturcio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_free_shell_and_token(t_token *all_token, t_shell *shell)
{
	t_token	*next_token;

	while (all_token)
	{
		next_token = all_token->next;
		free(all_token->value);
		free(all_token);
		all_token = next_token;
	}
	ft_free_shell(shell);
}

static char	*ft_read_line(int fd)
{
	char	buffer[2];
	char	*line;
	char	*temp;
	int		res;

	line = malloc(sizeof(char));
	if (!line)
		return (NULL);
	line[0] = 0;
	buffer[1] = 0;
	buffer[0] = 0;
	while (buffer[0] != '\n')
	{
		res = read(fd, buffer, 1);
		if (res <= 0 || res == EOF)
		{
			free(line);
			return (NULL);
		}
		temp = line;
		line = ft_strjoin(line, buffer);
		free(temp);
	}
	return (line);
}

static void	ft_read_stdin(int end[2], char *limiter, t_token *a, t_shell *shl)
{
	char	*line;
	int		len_line;

	close(end[0]);
	write(1, "here_doc> ", 10);
	line = ft_read_line(STDIN_FILENO);
	while (line)
	{
		len_line = ft_strlen(line) - 1;
		if (!ft_strncmp(line, limiter, len_line))
		{
			free(line);
			close(end[1]);
			ft_free_shell_and_token(a, shl);
			exit(EXIT_SUCCESS);
		}
		write(end[1], line, len_line + 1);
		write(1, "here_doc> ", 10);
		free(line);
		line = ft_read_line(STDIN_FILENO);
	}
	close(end[1]);
	ft_free_shell_and_token(a, shl);
	exit(EXIT_FAILURE);
}

void	ft_heredoc_continuation(t_shell *shell, pid_t pid, \
struct termios *original_config, int *end)
{
	int	status;

	close(end[1]);
	ft_signals_ign();
	waitpid(pid, &status, 0);
	tcsetattr(STDIN_FILENO, TCSANOW, original_config);
	ft_control_signals_main();
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
	{
		shell->exit_status = 130;
		shell->cmds->in = -1;
		close(end[0]);
	}
	else if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_FAILURE)
	{
		ft_printf("\nminishell: warning: here-document delimited "\
"by end-of-file (wanted 'delimiter')\n");
		shell->cmds->in = end[0];
	}
	else
		shell->cmds->in = end[0];
}

void	ft_heredoc(char *limiter, t_cmd *cmd, t_token *alltkn, t_shell *shell)
{
	pid_t			pid;
	int				end[2];
	struct termios	original_config;
	struct termios	heredoc_config;

	(void)cmd;
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
		ft_read_stdin(end, limiter, alltkn, shell);
		exit(EXIT_SUCCESS);
	}
	ft_heredoc_continuation(shell, pid, &original_config, end);
}
