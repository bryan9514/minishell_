/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 09:35:28 by yel-mens          #+#    #+#             */
/*   Updated: 2025/06/29 09:35:28 by yel-mens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_check_wrong_token(t_token *token, int is_cmd, t_shell *shell)
{
	t_token	*all_tkn;

	all_tkn = shell->tokens;
	if ((token->type != TOKEN_WORD && token->type != TOKEN_PIPE)
		&& (!token->value || !token->value[0]))
	{
		ft_free_token(all_tkn, shell);
		if (isatty(STDIN_FILENO))
			ft_putendl_fd("Please name your redirection", STDERR_FILENO);
		return (1);
	}
	if (token->type == TOKEN_PIPE && is_cmd == 0)
	{
		ft_free_token(all_tkn, shell);
		if (isatty(STDIN_FILENO))
			ft_putendl_fd("Empty pipe detected", STDERR_FILENO);
		return (1);
	}
	return (0);
}

static t_token	*ft_free_null_token(t_token *token, t_token **all_token)
{
	t_token	*temp;

	if (*all_token == token)
	{
		*all_token = (*all_token)->next;
		if (token->value)
			free(token->value);
		free(token);
		return (*all_token);
	}
	temp = *all_token;
	while (temp->next != token)
		temp = temp->next;
	temp->next = token->next;
	if (token->value)
		free(token->value);
	free(token);
	token = NULL;
	return (temp);
}

static int	ft_open_all_heredoc(t_token *all_token, t_shell *shell, int *is_cmd)
{
	t_token	*token;

	token = all_token;
	while (token)
	{
		if (token->type == TOKEN_HEREDOC)
		{
			ft_heredoc(token->value, token, shell);
			if (g_signal == MAIN_SIGINT)
			{
				token = all_token;
				while (token)
				{
					if (token->in > 0)
						close(token->in);
					token = token->next;
				}
				*is_cmd = 0;
				return (0);
			}
		}
		token = token->next;
	}
	return (1);
}

int	ft_check_token(t_token **all_token, t_shell *shell)
{
	t_token	*token;
	int		is_cmd;

	token = *all_token;
	is_cmd = 0;
	while (token)
	{
		if (token->type != TOKEN_PIPE)
			is_cmd = 1;
		if (ft_check_wrong_token(token, is_cmd, shell))
			return (0);
		if (token->type == TOKEN_PIPE)
			is_cmd = 0;
		if ((!token->value || !token->value[0]) && token->type == TOKEN_WORD)
			token = ft_free_null_token(token, all_token);
		if (token)
			token = token->next;
	}
	if (!is_cmd || !ft_open_all_heredoc(*all_token, shell, &is_cmd))
		ft_free_token(*all_token, shell);
	return (is_cmd);
}
