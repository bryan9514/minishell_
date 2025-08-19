/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:45:12 by yel-mens          #+#    #+#             */
/*   Updated: 2025/06/25 05:53:49 by yel-mens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	array = NULL;
}

void	ft_free_cmds(t_cmd *cmds)
{
	t_cmd	*next_cmd;

	next_cmd = NULL;
	while (cmds)
	{
		next_cmd = cmds->next;
		if (cmds->args)
			ft_free_array(cmds->args);
		if (cmds->in >= 0 && cmds->in != STDIN_FILENO)
			close(cmds->in);
		if (cmds->out >= 0 && cmds->out != STDOUT_FILENO)
			close(cmds->out);
		free(cmds);
		cmds = next_cmd;
	}
}

void	ft_free_env(t_env *env)
{
	t_env	*next_env;

	next_env = NULL;
	while (env)
	{
		next_env = env->next;
		free(env->data);
		free(env->var);
		free(env->value);
		free(env);
		env = next_env;
	}
}

void	ft_error(char *msg, int exit_code, t_shell *shell)
{
	if (!shell)
		exit(EXIT_FAILURE);
	perror(msg);
	ft_free_shell(shell);
	exit(exit_code);
}

void	ft_free_shell(t_shell *shell)
{
	if (shell)
	{
		if (shell->cmds)
			ft_free_cmds(shell->cmds);
		if (shell->env)
			ft_free_env(shell->env);
		if (shell->pids)
			free(shell->pids);
		if (shell->history)
			ft_free_history(shell->history);
		if (shell->tokens)
			ft_free_token(shell->tokens, shell);
		free(shell);
	}
}
