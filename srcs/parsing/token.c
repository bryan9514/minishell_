/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 10:18:43 by yel-mens          #+#    #+#             */
/*   Updated: 2025/06/29 15:35:10 by yel-mens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_put_token(t_token *token, t_shell *shell)
{
	t_token	*aux_token;

	if (shell->tokens)
	{
		aux_token = shell->tokens;
		while (aux_token->next)
			aux_token = aux_token->next;
		aux_token->next = token;
	}
	else
		shell->tokens = token;
}

static t_token	*ft_add_token(char *line, int *i, t_token_type t, t_shell *shl)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		ft_error("token malloc error", EXIT_MALLOC, shl);
	ft_put_token(token, shl);
	token->type = t;
	if (token->type == TOKEN_REDIR_IN || token->type == TOKEN_REDIR_OUT)
		*i += 1;
	if (token->type == TOKEN_HEREDOC || token->type == TOKEN_REDIR_APPEND)
		*i += 2;
	token->next = NULL;
	token->value = ft_get_next_word(line, i, t, shl);
	token->in = -1;
	return (token);
}

static t_token	*ft_add_token_pipe(int *i, t_shell *shell)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		ft_error("token malloc error", EXIT_MALLOC, shell);
	ft_put_token(token, shell);
	token->type = TOKEN_PIPE;
	token->next = NULL;
	token->value = NULL;
	token->in = -1;
	*i += 1;
	return (token);
}

static t_token	*ft_swtch_tkn(char *line, int *i, t_token **tkn, t_shell *shl)
{
	t_token	*cur_token;

	if (line[*i] == '<' && line[*i + 1] == '<')
		cur_token = ft_add_token(line, i, TOKEN_HEREDOC, shl);
	else if (line[*i] == '<')
		cur_token = ft_add_token(line, i, TOKEN_REDIR_IN, shl);
	else if (line[*i] == '>' && line[*i + 1] == '>')
		cur_token = ft_add_token(line, i, TOKEN_REDIR_APPEND, shl);
	else if (line[*i] == '>')
		cur_token = ft_add_token(line, i, TOKEN_REDIR_OUT, shl);
	else if (line[*i] == '|')
		cur_token = ft_add_token_pipe(i, shl);
	else
		cur_token = ft_add_token(line, i, TOKEN_WORD, shl);
	if (!(*tkn))
		*tkn = shl->tokens;
	return (cur_token);
}

t_token	*ft_tokeniser(char *line, t_shell *shell)
{
	t_token	*token;
	int		len;
	int		i;

	token = NULL;
	shell->tokens = token;
	len = ft_strlen(line);
	i = 0;
	while (i < len && ft_isspace(line[i]))
		i++;
	while (i < len)
	{
		if (!ft_swtch_tkn(line, &i, &token, shell))
		{
			ft_free_token(token, shell);
			return (NULL);
		}
		while (i < len && ft_isspace(line[i]))
			i++;
	}
	return (token);
}
