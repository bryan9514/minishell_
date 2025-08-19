/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brturcio <brturcio@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:42:29 by yel-mens          #+#    #+#             */
/*   Updated: 2025/07/01 11:51:29 by brturcio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_compare(char *var, t_env *current_env, int len)
{
	char	*current_var;
	int		i;

	current_var = current_env->var;
	if (len != (int) ft_strlen(current_var))
		return (0);
	i = 0;
	while (i < len)
	{
		if (var[i] != current_var[i])
			return (0);
		i++;
	}
	return (1);
}

t_env	*ft_search_env(char *var, t_shell *shell)
{
	int		len;
	t_env	*env;

	len = 0;
	while (var[len])
		len++;
	env = shell->env;
	while (env)
	{
		if (ft_compare(var, env, len))
			return (env);
		env = env->next;
	}
	return (NULL);
}

int	ft_unset_env(t_env *to_delete, t_shell *shell)
{
	if (!shell->env->next)
		shell->env = NULL;
	else
	{
		if (to_delete->prev)
			to_delete->prev->next = to_delete->next;
		if (to_delete->next)
			to_delete->next->prev = to_delete->prev;
	}
	free(to_delete->data);
	free(to_delete->var);
	free(to_delete->value);
	free(to_delete);
	return (0);
}

void	ft_append_env(char *data, t_shell *shell)
{
	t_env	*var_env;

	if (!data)
		ft_error("No data to append in env", EXIT_SYNTAX_ERROR, shell);
	var_env = malloc(sizeof(t_env));
	if (!var_env)
	{
		free(data);
		ft_error("new env var malloc error", EXIT_MALLOC, shell);
	}
	var_env->data = data;
	var_env->var = ft_extract_var(data);
	var_env->value = ft_extract_value(data);
	var_env->exporte = NOT_EXPORTE;
	var_env->next = NULL;
	var_env->prev = NULL;
	ft_append_env_continuatio(shell, var_env);
}

void	ft_init_env(char **env, t_shell *shell)
{
	char	path[PATH_MAX];
	int		i;

	if (!env)
	{
		if (!getcwd(path, PATH_MAX))
			ft_error("Cannot get the path", EXIT_ENV, shell);
		ft_append_env(ft_strjoin("PATH=", path), shell);
		return ;
	}
	i = 0;
	while (env[i])
	{
		ft_append_env(ft_strdup(env[i]), shell);
		i++;
	}
}
