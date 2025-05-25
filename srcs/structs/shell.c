/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:13:11 by yel-mens          #+#    #+#             */
/*   Updated: 2025/05/09 17:15:40 by yel-mens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	*init_shell(char **env)
{
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	if (!shell)
	{
		perror("shell malloc");
		exit(EXIT_MALLOC);
	}
	shell->cmds = NULL;
	shell->history = NULL;
	shell->env = NULL;
	shell->exit_status = EXIT_SUCCESS;
	ft_init_env(env, shell);
	return (shell);
}
