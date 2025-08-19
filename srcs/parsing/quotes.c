/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 17:29:08 by yel-mens          #+#    #+#             */
/*   Updated: 2025/06/24 14:02:44 by brturcio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_issep(char c)
{
	if (c == 0 || ft_isspace(c) || c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

static int	ft_dollar_check(char *line, int sg_quote, int begin)
{
	return (line[begin] == '$' && !sg_quote && !ft_issep(line[begin + 1])
		&& line[begin + 1] != '"' && line[begin + 1] != '\'');
}

static char	*ft_dup_from_line(int begin, int end, char *line, t_shell *shell)
{
	char	*word;
	int		i;
	int		sg_quote;
	int		db_quote;

	ft_dup_from_line_two(&i, &sg_quote, &db_quote);
	word = ft_calloc((end - begin) + 2, sizeof(char));
	if (!word)
		ft_error("malloc error", EXIT_MALLOC, shell);
	while (begin < end)
	{
		if (line[begin] == '\'' && !db_quote)
			sg_quote = (sg_quote + 1) % 2;
		else if (line[begin] == '"' && !sg_quote)
			db_quote = (db_quote + 1) % 2;
		else if (ft_dollar_check(line, sg_quote, begin))
			ft_dollar(line, &begin, &word, shell);
		else
			word[i++] = line[begin];
		while (word[i])
			i++;
		word[i + 1] = 0;
		begin++;
	}
	return (word);
}

static int	ft_go_end_word(char *line, int *i)
{
	int	sg_quote;
	int	db_quote;

	sg_quote = 0;
	db_quote = 0;
	while (line[*i])
	{
		if ((!sg_quote && !db_quote) && ft_issep(line[*i]))
			return (1);
		else if (!sg_quote && line[*i] == '"')
			db_quote = (db_quote + 1) % 2;
		else if (!db_quote && line[*i] == '\'')
			sg_quote = (sg_quote + 1) % 2;
		*i += 1;
	}
	if (!line[*i] && (sg_quote || db_quote))
	{
		ft_printf("minishell : Quotes not closed\n");
		return (0);
	}
	return (1);
}

char	*ft_get_next_word(char *line, int *i, t_token_type t, t_shell *shell)
{
	int		begin_word;
	int		end_word;
	char	*word;

	while (ft_isspace(line[*i]))
		*i += 1;
	begin_word = *i;
	if (!ft_go_end_word(line, i))
		return (NULL);
	end_word = *i;
	if (t == TOKEN_HEREDOC)
		word = ft_substr(line, begin_word, end_word - begin_word);
	else
		word = ft_dup_from_line(begin_word, end_word, line, shell);
	return (word);
}
