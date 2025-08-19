/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 08:26:31 by brturcio          #+#    #+#             */
/*   Updated: 2025/06/29 11:18:58 by yel-mens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal = NO_SIGNAL;

void	ft_print_prompt(t_shell *shell)
{
	t_env	*logname;
	t_env	*hostname;
	t_env	*pwd;

	if (!isatty(STDIN_FILENO))
		return ;
	logname = ft_search_env("LOGNAME", shell);
	hostname = ft_search_env("NAME", shell);
	pwd = ft_search_env("PWD", shell);
	if (logname)
		ft_printf(HGRN"%s"RST, logname->data + 8);
	if (hostname)
		ft_printf(CYAN"@%s"RST, hostname->data + 5);
	if (logname || hostname)
		write(1, ":", 1);
	if (pwd)
		ft_printf(HMAG"%s"RST, pwd->data + 4);
	write(1, "$\t", 2);
}

static int	continue_main(char **env, t_shell *shell)
{
	char	*line;

	ft_control_signals_main();
	ft_print_prompt(shell);
	ft_update_exit_status_by_signal(shell);
	line = ft_readline(shell);
	if (!line)
		return (1);
	if (!line[0])
	{
		free(line);
		return (0);
	}
	ft_init_history(line, shell);
	if (ft_parse(line, shell))
		ft_process(env, shell);
	else
	{
		if (shell->exit_status != EXIT_SIGINT)
			shell->exit_status = EXIT_SYNTAX_ERROR;
	}
	while (wait(NULL) != -1)
		;
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	int		last_status_exit;
	t_shell	*shell;

	(void) argc;
	(void) argv;
	printbanner();
	shell = init_shell(env);
	while (shell)
	{
		if (continue_main(env, shell))
		{
			ft_printf("exit\n");
			break ;
		}
	}
	last_status_exit = shell->exit_status;
	ft_free_shell(shell);
	return (last_status_exit);
}
