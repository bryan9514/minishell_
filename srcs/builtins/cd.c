/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brturcio <brturcio@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:57:58 by brturcio          #+#    #+#             */
/*   Updated: 2025/05/15 20:26:25 by brturcio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_cd_home(t_shell *shell)
{
	char	*home;
	char	*oldpwd;
	char	cwd[PATH_MAX];

	home = ft_get_val("HOME", shell);
	if (!home)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
		return (1);
	}
	oldpwd = ft_get_val("PWD", shell);
	if (chdir(home) == -1)
	{
		perror("minishell: cd");
		free(home);
		free(oldpwd);
		return (1);
	}
	if (oldpwd)
		ft_update_env("OLDPWD", oldpwd, shell);
	if (getcwd(cwd, PATH_MAX))
		ft_update_env("PWD", cwd, shell);
	free(home);
	free(oldpwd);
	return (0);
}

static int	ft_cd_oldpwd2(char *oldpwd, char *pwd, t_shell *shell)
{
	char	cwd[PATH_MAX];

	ft_putstr_fd(oldpwd, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	if (pwd)
		ft_update_env("OLDPWD", pwd, shell);
	if (getcwd(cwd, PATH_MAX))
		ft_update_env("PWD", cwd, shell);
	free(oldpwd);
	free(pwd);
	return (0);
}

static int	ft_cd_oldpwd(t_shell *shell)
{
	char	*oldpwd;
	char	*pwd;

	oldpwd = ft_get_val("OLDPWD", shell);
	if (!oldpwd)
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", STDERR_FILENO);
		return (1);
	}
	pwd = ft_get_val("PWD", shell);
	if (chdir(oldpwd) == -1)
	{
		perror ("minishell : cd -");
		free(pwd);
		free(oldpwd);
		return (1);
	}
	return (ft_cd_oldpwd2(oldpwd, pwd, shell));
}

int	ft_cd_builtins(t_cmd *cmd, t_shell *shell)
{
	if (cmd->args[1] && cmd->args[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", STDERR_FILENO);
		shell->exit_status = 1;
		return (1);
	}
	if (!cmd->args[1] || ft_strncmp(cmd->args[1], "~", 2) == 0)
		return (ft_cd_home(shell));
	if (ft_strncmp(cmd->args[1], "-", 2) == 0)
		return (ft_cd_oldpwd(shell));
	return (ft_cd_path(cmd->args[1], shell));
}
