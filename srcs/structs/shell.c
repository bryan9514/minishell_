/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brturcio <brturcio@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:13:11 by yel-mens          #+#    #+#             */
/*   Updated: 2025/06/12 08:08:45 by brturcio         ###   ########.fr       */
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
	shell->pids = NULL;
	shell->nb_cmds = 0;
	shell->exit_status = EXIT_SUCCESS;
	ft_init_env(env, shell);
	return (shell);
}
