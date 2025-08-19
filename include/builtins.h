/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brturcio <brturcio@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:18:42 by brturcio          #+#    #+#             */
/*   Updated: 2025/06/24 13:01:16 by brturcio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "structs.h"
# include "minishell.h"

# define PATH_MAX 4096
# define EXPORTE 1
# define NOT_EXPORTE 0

/*  builtins  */
int		ft_is_builtin(char *arg);
int		ft_is_builtin_no_fork(char *arg);
int		ft_no_fork(t_cmd *cmd, t_shell *shell);
void	ft_exec_builtins(t_cmd *cmd, t_shell *shell);

/*  cd_path  */
int		ft_cd_path(char *arg, t_shell *shell);

/*  cd  */
int		ft_cd_builtins(t_cmd *cmd, t_shell *shell);

/*  echo.c  */
int		ft_echo_builtins(t_cmd *cmd);

/*  env_utils  */
char	*ft_get_val(char *var, t_shell *shell);
char	*build_new_env(char *var, char *data);
char	*ft_update_env(char *var, char *data, t_shell *shell);

/*  env  */
int		ft_env_builtins(t_cmd *cmd, t_env *env);

/*  exit  */
void	ft_exit_builtins(t_cmd *cmd, t_shell *shell);

/*  export_utils  */
t_env	*ft_cread_env_copy(t_env *env);
void	ft_swap_env_content(t_env *a, t_env *b);
void	ft_sort_env_copy(t_env *head);

/*  export_utils2  */
void	ft_export_error_msj(char *arg, char *msj);
int		ft_parsing_export_arg(char *arg);
int		ft_check_equal(char *arg);
t_env	*ft_var_exists(t_env *env, char *arg);
t_env	*ft_find_env(t_shell *shell, char *var);

/*  export  */
int		ft_concat_env(char *var, char *value, t_env *node);
int		ft_export_builtins(t_shell *shell);

/*  pwd  */
int		ft_pwd_builtins(t_cmd *cmd);

/*  unset  */
int		ft_unset_builtins(t_shell *shell);

#endif
