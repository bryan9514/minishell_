/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brturcio <brturcio@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 12:52:59 by yel-mens          #+#    #+#             */
/*   Updated: 2025/07/01 11:36:02 by brturcio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_token_info(t_token *tkn, int tab_info[3])
{
	int	i;

	tab_info[1] = 0;
	tab_info[2] = 0;
	i = 0;
	while (tkn && tkn->type != TOKEN_PIPE)
	{
		if (tkn->type == TOKEN_REDIR_IN || tkn->type == TOKEN_HEREDOC
			|| tkn->type == TOKEN_REDIR_OUT || tkn->type == TOKEN_REDIR_APPEND)
			tab_info[1] += 1;
		if (tkn->type == TOKEN_WORD)
			tab_info[2] += 1;
		i++;
		tkn = tkn->next;
	}
	tab_info[0] = i;
}

static void	ft_place_token(t_token *token, t_token **tab_token, int tab_info[3])
{
	int	first;

	if (token->type == TOKEN_REDIR_IN || token->type == TOKEN_HEREDOC
		|| token->type == TOKEN_REDIR_OUT || token->type == TOKEN_REDIR_APPEND)
		first = 0;
	else
		first = tab_info[1];
	while (tab_token[first])
		first++;
	tab_token[first] = token;
}

static void	ft_link_token(t_token **tab_token, int len, t_token *last_token)
{
	t_token	*cur_token;
	int		i;

	if (len == 0)
		return ;
	i = 0;
	while (i < len - 1)
	{
		cur_token = tab_token[i];
		cur_token->next = tab_token[++i];
	}
	cur_token = tab_token[i];
	cur_token->next = last_token;
}

static void	ft_sort_token_continuation(t_shell *shell,
	t_token **token, t_token **tab_token, int *tab_info)
{
	if (*token && (*token)->type == TOKEN_PIPE)
		(*token)->next = ft_sort_token((*token)->next, shell);
	ft_link_token(tab_token, tab_info[0], *token);
	*token = tab_token[0];
	free(tab_token);
}

t_token	*ft_sort_token(t_token *token, t_shell *shell)
{
	t_token	**tab_token;
	int		tab_info[3];
	int		len;

	if (!token)
		return (NULL);
	ft_token_info(token, tab_info);
	if (tab_info[0] == 0)
		return (token);
	tab_token = malloc(sizeof(t_token *) * tab_info[0]);
	if (!tab_token)
		ft_error("sort tkn malloc error", EXIT_MALLOC, shell);
	len = tab_info[0];
	while (len-- > 0)
		tab_token[len] = NULL;
	while (token && token->type != TOKEN_PIPE)
	{
		ft_place_token(token, tab_token, tab_info);
		token = token->next;
	}
	ft_sort_token_continuation(shell, &token, tab_token, &tab_info[0]);
	return (token);
}
