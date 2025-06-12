/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brturcio <brturcio@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 08:26:31 by brturcio          #+#    #+#             */
/*   Updated: 2025/06/10 19:59:11 by brturcio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal = NO_SIGNAL;

// void	ft_print_prompt(t_shell *shell)
// {
// 	t_env	*logname;
// 	t_env	*hostname;
// 	t_env	*pwd;

// 	if (!isatty(STDIN_FILENO))
// 		return ;
// 	logname = ft_search_env("LOGNAME", shell);
// 	hostname = ft_search_env("NAME", shell);
// 	pwd = ft_search_env("PWD", shell);
// 	if (logname)
// 		ft_printf(HGRN"%s"RST, logname->data + 8);
// 	if (hostname)
// 		ft_printf(CYAN"@%s"RST, hostname->data + 5);
// 	if (logname || hostname)
// 		write(1, ":", 1);
// 	if (pwd)
// 		ft_printf(HMAG"%s"RST, pwd->data + 4);
// 	write(1, "$\t", 2);
// }

// static void	ft_handle_line(char *line, char **env, t_shell *shell)
// {
// 	ft_init_history(line, shell);
// 	ft_parse(line, shell);
// 	ft_process(env, shell);
// 	while (wait(NULL) != -1)
// 		;
// }

// static int	ft_check_signal(char *line)
// {
// 	if (g_signal == SIGINT)
// 	{
// 		g_signal = 0;
// 		if (line)
// 			free(line);
// 		return (1);
// 	}
// 	return (0);
// }

// int	main(int argc, char **argv, char **env)
// {
// 	t_shell	*shell;
// 	char	*line;

// 	(void) argc;
// 	(void) argv;
// 	// printbanner();
// 	shell = init_shell(env);
// 	ft_signals_control_main();
// 	while (shell)
// 	{
// 		g_signal = 0;
// 		ft_print_prompt(shell);
// 		line = get_next_line(STDIN_FILENO);
// 		if (ft_check_signal(line))
// 			continue ;
// 		if (!line)
// 			break ;
// 		ft_handle_line(line, env, shell);
// 	}
// 	ft_free_shell(shell);
// 	if (isatty(STDIN_FILENO))
// 		ft_printf(YELLOW"\nSEE YOU SOON !\n"RST);
// 	return (EXIT_SUCCESS);
// }


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

static void	ft_handle_line(char *line, char **env, t_shell *shell)
{
	add_history(line);
	ft_parse(line, shell);
	ft_process(env, shell);
	while (wait(NULL) != -1)
		;
}

int	main(int argc, char **argv, char **env)
{
	t_shell	*shell;
	char	*line;
	char	*prompt;

	(void) argc;
	(void) argv;
	// printbanner();
	shell = init_shell(env);
	while (shell)
	{
		prompt = ft_print_prompt(shell);
		ft_control_signals_main();
		line = readline(prompt);
		free(prompt);
		// ft_update_exit_status_by_signal(shell);
		if (!line)
			break;
		// printf("DEBUG (main): exit_status = %d.\n", shell->exit_status);
		ft_handle_line(line, env, shell);
		free(line);
	}
	rl_clear_history();
	ft_free_shell(shell);
	return (EXIT_SUCCESS);
}
