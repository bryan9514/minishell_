/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brturcio <brturcio@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 10:10:14 by yel-mens          #+#    #+#             */
/*   Updated: 2025/07/01 16:17:05 by brturcio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

/* * * * * * *
*  readline *
* * * * * * * */

int		ft_switch_seq(unsigned char seq[4], char **line, t_shell *shell);

/* * * * * *
* parser *
* * * * * */

int		ft_parse(char *line, t_shell *shell);
int		ft_open_cmd(t_token	**token, t_cmd *cmd, t_shell *shell);

/* * * * * * *
* tokeniser *
* * * * * * * */

t_token	*ft_tokeniser(char *line, t_shell *shell);
t_token	*ft_sort_token(t_token *token, t_shell *shell);
char	*ft_get_next_word(char *line, int *i, t_token_type t, t_shell *shell);
void	ft_dollar(char *line, int *begin, char **word, t_shell *shell);
int		ft_check_token(t_token **token, t_shell *shell);
void	ft_free_token(t_token *token, t_shell *shell);
void	ft_dup_from_line_two(int *i, int *sg_quote, int *db_quote);

/* * * * *
* file *
* * * * * */

int		ft_open_infile(char *filename, t_cmd *cmd);
int		ft_open_outfile(char *filename, t_cmd *cmd, t_token_type type);
void	ft_open_pipe(t_cmd *cmd, t_shell *shell);
int		ft_heredoc_continuation(t_shell *shell, pid_t pid, \
struct termios *original_config, int *end);
void	ft_heredoc(char *limiter, t_token *tk, t_shell *shell);
int		ft_heredoc_in_cmd(t_cmd *cmd, t_token *token);
void	ft_read_stdin(int end[2], char *limiter, t_shell *shl);
void	ft_heredoc_exit(char *line, int end[2], t_shell *shl);
int		ft_limiter_check(char *limiter);
void	ft_free_shell_and_token(t_shell *shell, int exit_status);

#endif
