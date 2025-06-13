/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brturcio <brturcio@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 17:36:08 by brturcio          #+#    #+#             */
/*   Updated: 2025/06/13 07:22:31 by brturcio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset_builtins(t_shell *shell)
{
	char	**args;
	t_env	*env_to_delete;
	int		i;

	args = shell->cmds->args;
	i = 1;
	while (args[i])
	{
		env_to_delete = ft_find_env(shell, args[i]);
		if (!env_to_delete)
		{
			i++;
			continue ;
		}
		if (env_to_delete)
			ft_unset_env(env_to_delete, shell);
		i++;
	}
	return (0);
}
