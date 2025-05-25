/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 10:18:43 by yel-mens          #+#    #+#             */
/*   Updated: 2025/05/07 10:38:14 by yel-mens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_get_next_word(char *line, int *i)
{
	int		begin_word;
	int		end_word;
	int		j;
	char	*word;

	while (ft_isspace(line[*i]))
		*i += 1;
	begin_word = *i;
	while (line[*i] && !ft_isspace(line[*i]))
		*i += 1;
	end_word = (*i)++;
	word = malloc(sizeof(char) * (end_word - begin_word) + 1);
	if (!word)
		return (NULL);
	j = 0;
	while (j < end_word - begin_word)
	{
		word[j] = line[begin_word + j];
		j++;
	}
	word[j] = '\0';
	return (word);
}

static t_token	*ft_add_token(char *line, int *i, t_token_type t, t_shell *shl)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		ft_error("token malloc error", EXIT_MALLOC, shl);
	token->type = t;
	if (token->type == TOKEN_REDIR_IN || token->type == TOKEN_REDIR_OUT)
		*i += 1;
	if (token->type == TOKEN_HEREDOC || token->type == TOKEN_REDIR_APPEND)
		*i += 2;
	token->next = NULL;
	token->value = ft_get_next_word(line, i);
	if (!token->value)
	{
		free(token);
		ft_error("token value malloc error", EXIT_MALLOC, shl);
	}
	if (!token->value[0])
	{
		free(token->value);
		free(token);
		return (NULL);
	}
	return (token);
}

static t_token	*ft_add_token_pipe(int *i, t_shell *shell)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		ft_error("token malloc error", EXIT_MALLOC, shell);
	token->type = TOKEN_PIPE;
	token->next = NULL;
	token->value = NULL;
	*i += 1;
	return (token);
}

static void	ft_switch_token(char *line, int *i, t_token **token, t_shell *shell)
{
	t_token	*aux_token;
	t_token	*cur_token;

	if (line[*i] == '<' && line[*i + 1] == '<')
		cur_token = ft_add_token(line, i, TOKEN_HEREDOC, shell);
	else if (line[*i] == '<')
		cur_token = ft_add_token(line, i, TOKEN_REDIR_IN, shell);
	else if (line[*i] == '>' && line[*i + 1] == '>')
		cur_token = ft_add_token(line, i, TOKEN_REDIR_APPEND, shell);
	else if (line[*i] == '>')
		cur_token = ft_add_token(line, i, TOKEN_REDIR_OUT, shell);
	else if (line[*i] == '|')
		cur_token = ft_add_token_pipe(i, shell);
	else
		cur_token = ft_add_token(line, i, TOKEN_WORD, shell);
	if (*token)
	{
		aux_token = *token;
		while (aux_token->next)
			aux_token = aux_token->next;
		aux_token->next = cur_token;
	}
	else
		*token = cur_token;
}

t_token	*ft_tokeniser(char *line, t_shell *shell)
{
	t_token	*token;
	int		len;
	int		i;

	token = NULL;
	len = ft_strlen(line);
	i = 0;
	while (i < len && ft_isspace(line[i]))
		i++;
	while (i < len)
	{
		ft_switch_token(line, &i, &token, shell);
		while (i < len && ft_isspace(line[i]))
			i++;
	}
	return (token);
}
