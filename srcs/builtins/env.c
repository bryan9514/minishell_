/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brturcio <brturcio@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 13:52:59 by brturcio          #+#    #+#             */
/*   Updated: 2025/05/05 17:59:28 by brturcio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env_builtins(t_cmd *cmd, t_env *env)
{
	(void)cmd;
	while (env)
	{
		if (env->data && ft_strchr(env->data, '='))
			ft_putendl_fd(env->data, 1);
		env = env->next;
	}
	return (0);
}
