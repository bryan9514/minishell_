/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 10:56:04 by yel-mens          #+#    #+#             */
/*   Updated: 2025/05/06 15:18:52 by yel-mens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_get_path(t_shell *shell)
{
	char	**path;
	t_env	*env;

	env = ft_search_env("PATH", shell);
	if (env)
		path = ft_split(env->data + 5, ':');
	else
	{
		path = malloc(sizeof(char *));
		path[0] = NULL;
	}
	return (path);
}

static int	ft_search_path(char *cmd_name, char **args, char **path)
{
	int		i;
	char	*arg;
	char	*cmd_path;

	i = 0;
	while (path[i])
	{
		arg = ft_strjoin("/", cmd_name);
		cmd_path = ft_strjoin(path[i], arg);
		free(arg);
		if (!access(cmd_path, X_OK))
		{
			ft_free_array(path);
			free(cmd_name);
			args[0] = cmd_path;
			return (1);
		}
		free(cmd_path);
		i++;
	}
	ft_free_array(path);
	return (0);
}

static char	**ft_access(char **args, t_shell *shell)
{
	int		i;
	char	*cmd_name;
	char	**path;

	if (ft_is_builtin(args[0]))
		return (args);
	path = ft_get_path(shell);
	cmd_name = args[0];
	if (ft_search_path(cmd_name, args, path))
		return (args);
	if (!access(cmd_name, X_OK))
		return (args);
	perror(cmd_name);
	i = 0;
	while (args[i])
	{
		free(args[i]);
		args[i] = NULL;
		i++;
	}
	free(args);
	args = NULL;
	return (NULL);
}

static int	nb_word(t_token *token)
{
	int	i;

	i = 0;
	while (token && token->type != TOKEN_PIPE)
	{
		if (token->type == TOKEN_WORD)
			i++;
		token = token->next;
	}
	return (i);
}

int	ft_open_cmd(t_token	**token, t_cmd *cmd, t_shell *shell)
{
	int		nb_args;
	int		i;
	int		success;
	char	**args;

	nb_args = nb_word(*token);
	args = malloc(sizeof(char *) * (nb_args + 1));
	if (!args)
		return (0);
	success = 1;
	i = 0;
	while (i < nb_args)
	{
		if ((*token)->type == TOKEN_WORD)
		{
			args[i] = ft_strdup((*token)->value);
			if (!args[i++])
				success = 0;
		}
		if (i != nb_args)
			*token = (*token)->next;
	}
	args[i] = NULL;
	cmd->args = ft_access(args, shell);
	return (success);
}
