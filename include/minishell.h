/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:47:34 by brturcio          #+#    #+#             */
/*   Updated: 2025/06/27 17:20:53 by yel-mens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/ioctl.h>
// # include <readline/readline.h>
// # include <readline/history.h>
# include <limits.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <termios.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include "libft.h"
# include "builtins.h"
# include "structs.h"
# include "exit_codes.h"
# include "parsing.h"
# include "signals.h"

# define HGRN	"\e[0;92m"
# define HMAG	"\e[0;95m"
# define BLACK	"\033[0;30m"
# define RED	"\033[0;31m"
# define GREEN	"\033[0;32m"
# define YELLOW	"\033[0;33m"
# define BLUE	"\033[0;34m"
# define PURPLE	"\033[0;35m"
# define CYAN	"\033[0;36m"
# define WHITE	"\033[0;37m"
# define RST	"\033[0m"

# define MAX_LINE_LEN 1024

extern volatile sig_atomic_t	g_signal;

void	printbanner(void);
void	ft_print_prompt(t_shell *shell);
char	*ft_readline(t_shell *shell);
void	ft_child_process(t_cmd *cmd, char **env, t_shell *shell);
void	ft_process(char **env, t_shell *shell);
int		ft_init_process(char **env, t_shell *shell, int i);
int		ft_count_cmds(t_cmd *cmds);

#endif
