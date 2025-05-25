/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 22:47:10 by yel-mens          #+#    #+#             */
/*   Updated: 2025/05/09 12:27:13 by yel-mens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ft_init_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->in = STDIN_FILENO;
	cmd->out = STDOUT_FILENO;
	cmd->next = NULL;
	return (cmd);
}

static int	ft_manage_token(t_token **tkn, t_cmd *cmd, t_token *a, t_shell *s)
{
	int	success;

	success = 1;
	if ((*tkn)->type == TOKEN_REDIR_IN)
		success = ft_open_infile((*tkn)->value, cmd);
	else if ((*tkn)->type == TOKEN_REDIR_OUT
		|| (*tkn)->type == TOKEN_REDIR_APPEND)
		success = ft_open_outfile((*tkn)->value, cmd, (*tkn)->type);
	else if ((*tkn)->type == TOKEN_WORD)
		success = ft_open_cmd(tkn, cmd, s);
	else if ((*tkn)->type == TOKEN_PIPE)
		ft_open_pipe(cmd, s);
	else if ((*tkn)->type == TOKEN_HEREDOC)
		ft_heredoc((*tkn)->value, cmd, a, s);
	return (success);
}

static void	ft_free_token(t_token *token)
{
	t_token	*next_token;

	while (token)
	{
		next_token = token->next;
		free(token->value);
		free(token);
		token = next_token;
	}
}

void	ft_parse(char *line, t_shell *shell)
{
	t_token	*token;
	t_token	*all_token;
	t_cmd	*cmd;

	all_token = ft_tokeniser(line, shell);
	token = ft_sort_token(all_token);
	all_token = token;
	cmd = ft_init_cmd();
	if (!cmd)
		ft_error("cmd malloc error", EXIT_MALLOC, shell);
	shell->cmds = cmd;
	while (token)
	{
		if (!ft_manage_token(&token, cmd, all_token, shell))
			break ;
		if (token->type == TOKEN_PIPE)
			cmd = cmd->next;
		if (token)
			token = token->next;
	}
	ft_free_token(all_token);
}
