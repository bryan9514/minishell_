/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:12:28 by brturcio          #+#    #+#             */
/*   Updated: 2025/05/09 17:29:26 by yel-mens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_check_access(char *arg, char *pwd)
{
	if (access(arg, F_OK) == -1)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		free(pwd);
		return (1);
	}
	return (0);
}

static int	check_directory(char *arg)
{
	struct stat	info;

	if (stat(arg, &info) == -1)
	{
		perror ("stat");
		return (1);
	}
	if (!S_ISDIR(info.st_mode))
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": Not a directory\n", STDERR_FILENO);
		return (1);
	}
	return (0);
}

int	ft_cd_path(char *arg, t_shell *shell)
{
	char	cwd[PATH_MAX];
	char	*pwd;

	pwd = ft_get_val("PWD", shell);
	if (ft_check_access(arg, pwd))
		return (1);
	if (check_directory(arg))
	{
		free(pwd);
		return (1);
	}
	if (chdir(arg) == -1)
	{
		perror("minishell: cd");
		free(pwd);
		return (1);
	}
	if (pwd)
		ft_update_env("OLDPWD", pwd, shell);
	if (getcwd(cwd, PATH_MAX))
		ft_update_env("PWD", cwd, shell);
	free(pwd);
	return (0);
}
