/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brturcio <brturcio@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 10:44:05 by brturcio          #+#    #+#             */
/*   Updated: 2025/05/25 20:25:46 by brturcio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "minishell.h"

// À voir si j’en aurai besoin
typedef enum e_context
{
	CTX_PROMPT,
	CTX_EXEC,
	CTX_HEREDOC
}	t_context;

void	ft_sigint_handler(int signal);
void	ft_signals_control_main(void);

#endif
