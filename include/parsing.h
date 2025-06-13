/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brturcio <brturcio@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 10:10:14 by yel-mens          #+#    #+#             */
/*   Updated: 2025/06/13 07:16:45 by brturcio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_STRING,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_HEREDOC
}			t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}				t_token;

/* * * * * * *
*  readline *
* * * * * * * */

int		ft_switch_seq(unsigned char seq[4], char **line, t_shell *shell);

/* * * * * *
* parser *
* * * * * */

void	ft_parse(char *line, t_shell *shell);
int		ft_open_cmd(t_token	**token, t_cmd *cmd, t_shell *shell);

/* * * * * * *
* tokeniser *
* * * * * * * */

t_token	*ft_tokeniser(char *line, t_shell *shell);
t_token	*ft_sort_token(t_token *token);

/* * * * *
* file *
* * * * * */

int		ft_open_infile(char *filename, t_cmd *cmd);
int		ft_open_outfile(char *filename, t_cmd *cmd, t_token_type type);
void	ft_open_pipe(t_cmd *cmd, t_shell *shell);
void	ft_heredoc_continuation(t_shell *shell, pid_t pid, \
struct termios *original_config, int *end);
void	ft_heredoc(char *limiter, t_cmd *cmd, t_token *token, t_shell *shell);

#endif
