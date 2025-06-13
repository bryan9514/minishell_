/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brturcio <brturcio@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:27:43 by brturcio          #+#    #+#             */
/*   Updated: 2025/06/13 07:22:14 by brturcio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export_error_msj(char *arg, char *msj)
{
	ft_putstr_fd("minishell: export: ", STDERR_FILENO);
	if (arg)
	{
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (msj)
		ft_putendl_fd(msj, STDERR_FILENO);
}

int	ft_parsing_export_arg(char *arg)
{
	int	i;

	i = 1;
	if (!ft_isalpha(arg[0]) && (arg[0] != '_'))
		return (1);
	while (arg[i] && !(arg[i] == '=' || (arg[i] \
== '+' && arg[i + 1] == '=')))
	{
		if (!ft_isalpha(arg[i]) && !ft_isdigit(arg[i]) \
&& !(arg[i] == '_'))
			return (1);
		i++;
	}
	return (0);
}

int	ft_check_equal(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '=')
			return (1);
		else if (arg[i] == '+' && arg[i + 1] == '=')
			return (2);
		i++;
	}
	return (0);
}

t_env	*ft_var_exists(t_env *env, char *arg)
{
	char	*var;

	var = ft_extract_var(arg);
	while (env)
	{
		if (ft_strcmp(env->var, var) == 0)
		{
			free(var);
			return (env);
		}
		env = env->next;
	}
	free(var);
	return (NULL);
}

t_env	*ft_find_env(t_shell *shell, char *var)
{
	t_env	*env;

	env = shell->env;
	while (env)
	{
		if (ft_strcmp(env->var, var) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}
