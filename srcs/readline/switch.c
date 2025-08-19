/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 09:29:46 by yel-mens          #+#    #+#             */
/*   Updated: 2025/05/20 09:29:46 by yel-mens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_change_history(unsigned char seq[4], t_shell *shell)
{
	if (!shell->history)
		return (1);
	if (seq[2] == 'A')
	{
		if (shell->history->next)
			shell->history = shell->history->next;
	}
	else if (seq[2] == 'B')
	{
		if (shell->history->prev)
			shell->history = shell->history->prev;
	}
	return (1);
}

static int	ft_manage_arrows(unsigned char seq[4], char **line, t_shell *shell)
{
	char	*new_line;

	if (read(STDIN_FILENO, &seq[1], 1) != 1
		|| read(STDIN_FILENO, &seq[2], 1) != 1 || g_signal != NO_SIGNAL)
	{
		if (*line || *line[0])
			seq[0] = '\n';
		free(*line);
		*line = NULL;
		return (-1);
	}
	if (seq[1] == '[')
	{
		if (!shell->history)
			return (1);
		new_line = ft_strdup(shell->history->line);
		if (ft_change_history(seq, shell) && *line)
			free(*line);
		*line = new_line;
		ft_printf("\r\033[K");
		ft_print_prompt(shell);
		ft_printf("%s", *line);
	}
	return (1);
}

static int	ft_backspace(char *line)
{
	int	len;

	if (!line)
		return (1);
	len = ft_strlen(line);
	if (len > 0)
	{
		ft_printf("\b \b");
		line[len - 1] = 0;
	}
	return (1);
}

static int	ft_ctrl_d(char **line)
{
	if (!*line)
		return (-1);
	if (!*line[0])
	{
		free(*line);
		*line = NULL;
		return (-1);
	}
	return (1);
}

int	ft_switch_seq(unsigned char seq[4], char **line, t_shell *shell)
{
	if (g_signal != NO_SIGNAL)
	{
		seq[0] = 0;
		if (*line || *line[0])
			seq[0] = '\n';
		free(*line);
		*line = NULL;
		return (-1);
	}
	if (seq[0] == 27)
		return (ft_manage_arrows(seq, line, shell));
	if (seq[0] == 127)
		return (ft_backspace(*line));
	if (seq[0] == 4)
		return (ft_ctrl_d(line));
	return (0);
}
