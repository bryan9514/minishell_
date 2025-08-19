/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_rd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brturcio <brturcio@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 10:56:20 by yel-mens          #+#    #+#             */
/*   Updated: 2025/07/01 15:21:15 by brturcio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_read_line(int fd, t_shell *shell)
{
	char	buffer[2];
	char	*line;
	char	*temp;
	int		res;

	line = malloc(sizeof(char));
	if (!line)
		ft_error("line heredoc malloc error", EXIT_MALLOC, shell);
	line[0] = 0;
	buffer[1] = 0;
	buffer[0] = 0;
	while (buffer[0] != '\n')
	{
		res = read(fd, buffer, 1);
		if (res <= 0 || res == EOF || g_signal == MAIN_SIGINT)
		{
			free(line);
			return (NULL);
		}
		temp = line;
		line = ft_strjoin(line, buffer);
		free(temp);
	}
	return (line);
}

static char	*ft_dollar_env(char *line, int begin, t_shell *shell)
{
	int		i;
	t_env	*env;
	char	*tab;

	i = begin + 1;
	while (ft_isalnum(line[i]))
		i++;
	tab = ft_substr(line, begin + 1, i - begin - 1);
	if (!tab)
	{
		free(line);
		ft_error("strdup failed at $", EXIT_MALLOC, shell);
	}
	env = ft_search_env(tab, shell);
	free(tab);
	if (!env)
		tab = ft_calloc(1, sizeof(char));
	else
		tab = ft_strdup(env->value);
	return (tab);
}

static char	*ft_join_tab_line(char *line, char *tab, int ends[2], t_shell *shl)
{
	char	*new_line;
	int		len;
	int		i;
	int		j;

	new_line = malloc(sizeof(char) * (ft_strlen(line) + ft_strlen(tab) + 1));
	if (!new_line)
	{
		free(tab);
		free(line);
		ft_error("new_line malloc error at $", EXIT_MALLOC, shl);
	}
	i = -1;
	while (++i < ends[0])
		new_line[i] = line[i];
	len = ft_strlen(tab);
	j = -1;
	while (++j < len)
		new_line[i + j] = tab[j];
	while (line[++i + ends[1]])
		new_line[i + j - 1] = line[i + ends[1]];
	new_line[i + j - 1] = 0;
	free(line);
	free(tab);
	return (new_line);
}

static char	*ft_dollar_heredoc(char *line, t_shell *shell)
{
	int		i;
	int		begin;
	int		ends[2];
	char	*tab;

	i = 0;
	while (line[i] && line[i] != '$')
		i++;
	if (!line[i])
		return (line);
	begin = i;
	if (line[begin + 1] == '$' && !ft_isalnum(line[begin + 2]))
		tab = ft_itoa(shell->exit_status);
	else
		tab = ft_dollar_env(line, begin, shell);
	if (!tab)
	{
		free(line);
		ft_error("tab not malloced in $", EXIT_MALLOC, shell);
	}
	while (ft_isalnum(line[++i]))
		ends[1] = i - begin;
	ends[0] = begin;
	return (ft_join_tab_line(line, tab, ends, shell));
}

void	ft_read_stdin(int end[2], char *limiter, t_shell *shl)
{
	char	*line;
	int		expand;

	expand = ft_limiter_check(limiter);
	ft_printf("here_doc> ");
	line = ft_read_line(STDIN_FILENO, shl);
	while (line)
	{
		if ((int)(ft_strlen(line) - 1) == (int)ft_strlen(limiter)
			&& !ft_strncmp(line, limiter, ft_strlen(line) - 1))
			ft_heredoc_exit(line, end, shl);
		if (expand)
			line = ft_dollar_heredoc(line, shl);
		write(end[1], line, ft_strlen(line));
		ft_printf("here_doc> ");
		free(line);
		line = ft_read_line(STDIN_FILENO, shl);
	}
	close(end[1]);
	if (g_signal == MAIN_SIGINT)
		ft_free_shell_and_token(shl, EXIT_SIGINT);
	ft_free_shell_and_token(shl, EXIT_FAILURE);
}
