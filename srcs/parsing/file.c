/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 23:15:55 by yel-mens          #+#    #+#             */
/*   Updated: 2025/05/06 22:13:17 by yel-mens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_open_infile(char *filename, t_cmd *cmd)
{
	if (cmd->in > 0 && cmd->in != STDIN_FILENO)
		close(cmd->in);
	cmd->in = open(filename, O_RDONLY);
	if (cmd->in < 0)
	{
		perror(filename);
		return (0);
	}
	return (1);
}

int	ft_open_outfile(char *filename, t_cmd *cmd, t_token_type type)
{
	if (cmd->out > 0 && cmd->out != STDOUT_FILENO)
		close(cmd->out);
	if (type == TOKEN_REDIR_OUT)
		cmd->out = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		cmd->out = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (cmd->out < 0)
	{
		perror(filename);
		return (0);
	}
	return (1);
}

void	ft_open_pipe(t_cmd *cmd, t_shell *shell)
{
	t_cmd	*new_cmd;
	int		end[2];

	new_cmd = ft_init_cmd();
	if (!new_cmd)
		ft_error("malloc cmd error", EXIT_MALLOC, shell);
	if (pipe(end) < 0)
		ft_error("pipe error", EXIT_FD, shell);
	if (cmd->out == STDOUT_FILENO)
		cmd->out = end[1];
	else
		close(end[1]);
	new_cmd->in = end[0];
	cmd->next = new_cmd;
}
