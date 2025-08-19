/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 10:52:57 by yel-mens          #+#    #+#             */
/*   Updated: 2025/06/29 10:52:57 by yel-mens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_search_exit_status(char *word, t_shell *shell)
{
	char	*tab;
	char	*temp;

	temp = ft_itoa(shell->exit_status);
	tab = ft_strjoin(word, temp);
	free(temp);
	return (tab);
}

static char	*ft_dollar_continuation(char *line,
	int *begin, char **word, t_shell *shell)
{
	char	*tab;
	t_env	*env;
	int		i;

	i = *begin + 1;
	while (ft_isalnum(line[i]))
		i++;
	tab = ft_substr(line, *begin + 1, i - *begin - 1);
	*begin = i - 1;
	if (!tab)
	{
		perror("substr failed in $");
		return (NULL);
	}
	*begin = i - 1;
	env = ft_search_env(tab, shell);
	free(tab);
	if (!env)
		return (NULL);
	tab = ft_strjoin(*word, env->value);
	if (!tab)
		perror("strjoin failed in $");
	return (tab);
}

void	ft_dollar(char *line, int *begin, char **word, t_shell *shell)
{
	char	*tab;
	int		i;

	i = *begin + 1;
	while (ft_isalnum(line[i]))
		i++;
	if (line[*begin + 1] == '?' && ++i)
		tab = ft_search_exit_status(*word, shell);
	else
		tab = ft_dollar_continuation(line, begin, word, shell);
	if (!tab)
		return ;
	*begin = i - 1;
	free(*word);
	*word = malloc((ft_strlen(tab) + ft_strlen(line)) * sizeof(char));
	if (!*word)
		return (free(tab), ft_error("malloc error", EXIT_MALLOC, shell));
	ft_strlcpy(*word, tab, ft_strlen(tab) + 1);
	free(tab);
}
