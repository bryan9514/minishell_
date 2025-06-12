/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brturcio <brturcio@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 17:23:25 by yel-mens          #+#    #+#             */
/*   Updated: 2025/06/12 12:23:07 by brturcio         ###   ########.fr       */
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

void	ft_heredoc(char *limiter, t_cmd *cmd, t_token *alltkn, t_shell *shell)
{
	pid_t	pid;
	int		end[2];

	if (pipe(end) < 0)
		ft_error("Cannot open pipe in heredoc", EXIT_FD, shell);
	pid = fork();
	if (pid < 0)
		ft_error("fork in heredoc failed", EXIT_FD, shell);
	if (!pid)
		ft_read_stdin(end, limiter, alltkn, shell);
	if (pid == 0)
	{
		ft_control_signals_heredoc();

	}
	close(end[1]);
	waitpid(pid, NULL, 0);
	cmd->in = end[0];
}

// void	ft_heredoc(char *limiter, t_cmd *cmd, t_token *alltkn, t_shell *shell)
// {
// 	int				end[2];
// 	pid_t			pid;
// 	int				status;
// 	struct termios	original_termios;
// 	struct termios	heredoc_termios;

// 	// --- DECLARACIONES CORREGIDAS ---
// 	// Guardar atributos originales y desactivar ECHOCTL
// 	tcgetattr(STDIN_FILENO, &original_termios);
// 	heredoc_termios = original_termios;
// 	heredoc_termios.c_lflag &= ~ECHOCTL;
// 	tcsetattr(STDIN_FILENO, TCSANOW, &heredoc_termios);
// 	if (pipe(end) < 0)
// 		ft_error("Cannot open pipe in heredoc", EXIT_FD, shell);
// 	pid = fork();
// 	if (pid < 0)
// 		ft_error("fork in heredoc failed", EXIT_FD, shell);
// 	if (pid == 0) // Proceso Hijo
// 	{
// 		// El hijo debe restaurar los termios originales para no afectar su propio estado
// 		// tcsetattr(STDIN_FILENO, TCSANOW, &original_termios);
// 		ft_control_signals_heredoc();
// 		ft_read_stdin(end, limiter, alltkn, shell);
// 	}
// 	// LÓGICA DEL PADRE
// 	signal(SIGINT, SIG_IGN);
// 	signal(SIGQUIT, SIG_IGN);
// 	close(end[1]);
// 	waitpid(pid, &status, 0);
// 	// Restaurar los atributos originales de la terminal en el padre
// 	tcsetattr(STDIN_FILENO, TCSANOW, &original_termios);
// 	// ft_control_signals_main();
// 	// --- USO DEL PARÁMETRO 'cmd' PARA CORREGIR EL ERROR ---
// 	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
// 	{
// 		close(end[0]);
// 		cmd->in = -1; // Marcar como inválido para que no se ejecute el comando
// 		shell->exit_status = 130;
// 	}
// 	else
// 	{
// 		cmd->in = end[0]; // Asignar el pipe de lectura como entrada del comando
// 	}
// }
