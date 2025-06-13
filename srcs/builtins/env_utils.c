/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brturcio <brturcio@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:00:01 by brturcio          #+#    #+#             */
/*   Updated: 2025/06/13 07:30:46 by brturcio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_val(char *var, t_shell *shell)
{
	t_env	*env;

	env = ft_var_exists(shell->env, var);
	if (!env || !env->data)
		return (NULL);
	return (ft_strdup(env->value));
}

char	*build_new_env(char *var, char *data)
{
	char	*tmp;
	char	*result;

	tmp = ft_strjoin(var, "=");
	if (!tmp)
		return (NULL);
	result = ft_strjoin(tmp, data);
	free(tmp);
	return (result);
}

char	*ft_update_env(char *var, char *data, t_shell *shell)
{
	t_env	*env;
	char	*new_data;

	env = ft_var_exists(shell->env, var);
	if (!env)
	{
		new_data = build_new_env(var, data);
		if (!new_data)
			return (NULL);
		ft_append_env(ft_strdup(new_data), shell);
		return (new_data);
	}
	new_data = build_new_env(var, data);
	if (!new_data)
		return (NULL);
	free(env->data);
	free(env->value);
	free(env->var);
	env->data = new_data;
	env->var = ft_extract_var(new_data);
	env->value = ft_extract_value(new_data);
	return (env->data);
}
