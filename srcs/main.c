/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brturcio <brturcio@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 08:26:31 by brturcio          #+#    #+#             */
/*   Updated: 2025/06/13 09:14:00 by brturcio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal = NO_SIGNAL;

char	*ft_print_prompt(t_shell *shell)
{
	char	*prompt;
	t_env	*logname;
	char	*tmp;
	char	pwd[BUFSIZ];

	if (!getcwd(pwd, sizeof(pwd)))
		return (ft_strdup(HGRN"minishell $> "RST));
	logname = ft_find_env(shell, "LOGNAME");
	if (!logname)
		logname->value = "user";
	prompt = ft_strjoin(HGRN, logname->value);
	prompt = ft_strjoin_free(prompt, ":");
	prompt = ft_strjoin_free(prompt, RST);
	tmp = ft_strjoin(prompt, HMAG);
	free(prompt);
	prompt = tmp;
	prompt = ft_strjoin_free(prompt, pwd);
	prompt = ft_strjoin_free(prompt, RST);
	prompt = ft_strjoin_free(prompt, "$> ");
	return (prompt);
}

static int	continue_main(char **env, t_shell *shell)
{
	char	*prompt;
	char	*line;

	prompt = ft_print_prompt(shell);
	ft_control_signals_main();
	line = readline(prompt);
	free(prompt);
	ft_update_exit_status_by_signal(shell);
	if (!line)
		return (1);
	if (line[0] != '\0')
		add_history(line);
	ft_parse(line, shell);
	ft_process(env, shell);
	while (wait(NULL) != -1)
		;
	free(line);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	int		last_status_exit;
	t_shell	*shell;

	(void) argc;
	(void) argv;
	// printbanner();
	shell = init_shell(env);
	while (shell)
	{
		if (continue_main(env, shell))
		{
			write (STDOUT_FILENO, "exit\n", 5);
			break ;
		}
	}
	last_status_exit = shell->exit_status;
	rl_clear_history();
	ft_free_shell(shell);
	return (last_status_exit);
}
