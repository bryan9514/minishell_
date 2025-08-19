/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:24:29 by yel-mens          #+#    #+#             */
/*   Updated: 2025/05/19 16:24:29 by yel-mens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static struct termios	ft_no_raw_and_echo_mode(void)
{
	struct termios	oldt;
	struct termios	newt;

	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	newt.c_lflag |= ISIG;
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	return (oldt);
}

static char	*ft_join_to_line(unsigned char seq[4], char *line, t_shell *shell)
{
	char	*new_line;
	char	*malloc_seq;
	int		i;

	malloc_seq = malloc(sizeof(char) * 4);
	if (!malloc_seq)
	{
		if (line)
			free(line);
		ft_error("malloc sequence error", EXIT_MALLOC, shell);
	}
	ft_bzero(malloc_seq, 4);
	i = -1;
	while (seq[++i] && i < 4)
		malloc_seq[i] = seq[i];
	if (line)
	{
		new_line = ft_strjoin(line, malloc_seq);
		if (!new_line)
			perror("\nstrjoin failed in readline");
		free(line);
		free(malloc_seq);
		return (new_line);
	}
	return (malloc_seq);
}

static char	*ft_free_line(char *line, unsigned char seq[4])
{
	if (g_signal != NO_SIGNAL)
	{
		if (line)
			free(line);
		return (ft_strjoin("\0", ""));
	}
	if (!line && seq[0] == '\n')
		return (ft_strjoin("\0", ""));
	return (line);
}

char	*ft_readline(t_shell *shell)
{
	struct termios	oldt;
	unsigned char	seq[4];
	char			*line;
	int				swtch;

	line = NULL;
	oldt = ft_no_raw_and_echo_mode();
	ft_bzero(seq, sizeof(seq));
	while (read(STDIN_FILENO, &seq[0], 1) == 1 && seq[0] != '\n')
	{
		swtch = ft_switch_seq(seq, &line, shell);
		if (swtch == -1)
			break ;
		if (!swtch)
		{
			line = ft_join_to_line(seq, line, shell);
			ft_printf("%s", seq);
		}
		ft_bzero(seq, sizeof(seq));
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	ft_printf("\n");
	return (ft_free_line(line, seq));
}
