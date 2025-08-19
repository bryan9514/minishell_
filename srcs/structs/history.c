/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brturcio <brturcio@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 17:24:58 by yel-mens          #+#    #+#             */
/*   Updated: 2025/06/24 13:36:52 by brturcio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_hist	*ft_add_first_history(t_hist *new_history, t_shell *shell)
{
	t_hist	*history;

	history = shell->history;
	while (history->prev)
		history = history->prev;
	history->prev = new_history;
	return (history);
}

void	ft_init_history(char *line, t_shell *shell)
{
	t_hist	*history;

	history = malloc(sizeof(t_hist));
	if (!history)
	{
		free(line);
		ft_error("history malloc error", EXIT_MALLOC, shell);
	}
	history->line = line;
	if (shell->history)
		history->next = ft_add_first_history(history, shell);
	else
		history->next = NULL;
	history->prev = NULL;
	shell->history = history;
}

void	ft_free_history(t_hist *history)
{
	t_hist	*next_hist;

	if (!history)
		return ;
	while (history->prev)
		history = history->prev;
	while (history)
	{
		next_hist = history->next;
		free(history->line);
		free(history);
		history = next_hist;
	}
}
