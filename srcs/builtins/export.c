/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brturcio <brturcio@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 10:17:11 by brturcio          #+#    #+#             */
/*   Updated: 2025/06/13 07:21:54 by brturcio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_printf_export(t_env *env)
{
	t_env	*env_copy;
	t_env	*tmp;

	env_copy = ft_cread_env_copy(env);
	if (!env_copy)
		return (1);
	ft_sort_env_copy(env_copy);
	tmp = env_copy;
	while (tmp)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(tmp->var, STDOUT_FILENO);
		if (ft_strchr(tmp->data, '='))
		{
			ft_putstr_fd("=\"", STDOUT_FILENO);
			ft_putstr_fd(tmp->value, STDOUT_FILENO);
			ft_putstr_fd("\"", STDOUT_FILENO);
		}
		ft_putstr_fd("\n", STDOUT_FILENO);
		tmp = tmp->next;
	}
	ft_free_env(env_copy);
	return (0);
}

int	ft_concat_env(char *var, char *value, t_env *node)
{
	char	*joined;
	char	*new_data;

	if (!node || !value || !node->value)
		return (1);
	joined = ft_strjoin(node->value, value);
	if (!joined)
		return (1);
	new_data = build_new_env(var, joined);
	free(joined);
	if (!new_data)
		return (1);
	free(node->data);
	free(node->value);
	free(node->var);
	node->data = new_data;
	node->var = ft_extract_var(new_data);
	node->value = ft_extract_value(new_data);
	return (0);
}

static void	ft_update_or_append_env(t_shell *shell, int equal, \
char *var, char *value)
{
	t_env	*existing;

	existing = ft_var_exists(shell->env, var);
	if (existing)
	{
		if (equal == 1)
			ft_update_env(var, value, shell);
		else if (equal == 2)
			ft_concat_env(var, value, existing);
	}
	else
	{
		if (equal)
			ft_append_env(build_new_env(var, value), shell);
		else
			ft_append_env(ft_strdup(var), shell);
	}
}

static int	ft_export_with_arg(t_shell *shell, char **args)
{
	int		equal;
	char	*var;
	char	*value;

	equal = ft_check_equal(args[1]);
	var = ft_extract_var(args[1]);
	value = ft_extract_value(args[1]);
	if (!var || !value)
	{
		free(var);
		free(value);
		return (1);
	}
	ft_update_or_append_env(shell, equal, var, value);
	free(var);
	free(value);
	return (0);
}

int	ft_export_builtins(t_shell *shell)
{
	if (!shell->cmds->args[1])
		return (ft_printf_export(shell->env));
	if (ft_parsing_export_arg(shell->cmds->args[1]) || \
(shell->cmds->args[1] && shell->cmds->args[2]))
	{
		ft_export_error_msj(shell->cmds->args[1], \
"not a valid identifier");
		return (1);
	}
	if (ft_export_with_arg(shell, shell->cmds->args))
		return (1);
	return (0);
}
