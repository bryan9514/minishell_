/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 11:45:47 by brturcio          #+#    #+#             */
/*   Updated: 2025/05/09 17:28:30 by yel-mens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd_builtins(t_cmd *cmd)
{
	char	*rute;

	(void)cmd;
	rute = getcwd(NULL, 0);
	if (!rute)
	{
		ft_putstr_fd("minishell: pwd: getcwd failed\n", STDERR_FILENO);
		return (1);
	}
	ft_putstr_fd(rute, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	free(rute);
	return (0);
}
