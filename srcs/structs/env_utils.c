/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brturcio <brturcio@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 18:22:00 by brturcio          #+#    #+#             */
/*   Updated: 2025/07/01 11:56:11 by brturcio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_extract_var(char *data)
{
	int		len;
	char	*sep;
	char	*value;

	sep = ft_strchr(data, '=');
	if (!sep)
		return (ft_strdup(data));
	len = sep - data;
	if (len > 0 && data[len -1] == '+')
		len --;
	value = ft_substr(data, 0, len);
	return (value);
}

char	*ft_extract_value(char *data)
{
	char	*sep;
	char	*tmp;
	char	*value;
	int		len;

	sep = ft_strchr(data, '=');
	if (!sep)
		return (ft_strdup(""));
	tmp = sep + 1;
	len = ft_strlen(tmp);
	if (len >= 2 && ((tmp[0] == '"' && tmp[len - 1] == '"')
			|| (tmp[0] == '\'' && tmp[len - 1] == '\'')))
		value = ft_substr(tmp, 1, len - 2);
	else
		value = ft_strdup(tmp);
	return (value);
}

void	ft_append_env_continuatio(t_shell *shell, t_env *var_env)
{
	t_env	*env;

	if (!shell->env)
	{
		shell->env = var_env;
		return ;
	}
	env = shell->env;
	while (env->next)
		env = env->next;
	var_env->prev = env;
	env->next = var_env;
}
