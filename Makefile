# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: brturcio <brturcio@student.42angouleme.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/01 07:16:59 by brturcio          #+#    #+#              #
#    Updated: 2025/07/01 14:56:02 by brturcio         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= minishell
CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror -g


DIR_SRCS	:= srcs
DIR_OBJS	:= objs
DIR_LIBFT	:= libft

SRCS			:=	$(DIR_SRCS)/banner.c $(DIR_SRCS)/main.c $(DIR_SRCS)/free.c	\
					$(DIR_SRCS)/builtins/builtins.c $(DIR_SRCS)/builtins/echo.c	\
					$(DIR_SRCS)/builtins/env_utils.c $(DIR_SRCS)/builtins/env.c	\
					$(DIR_SRCS)/builtins/pwd.c $(DIR_SRCS)/builtins/cd.c		\
					$(DIR_SRCS)/builtins/export.c $(DIR_SRCS)/builtins/unset.c	\
					$(DIR_SRCS)/builtins/export_utils.c							\
					$(DIR_SRCS)/builtins/export_utils2.c 						\
					$(DIR_SRCS)/builtins/cd_path.c $(DIR_SRCS)/builtins/exit.c	\
					$(DIR_SRCS)/structs/env.c $(DIR_SRCS)/structs/env_utils.c	\
					$(DIR_SRCS)/structs/shell.c									\
					$(DIR_SRCS)/structs/history.c								\
					$(DIR_SRCS)/parsing/parse.c $(DIR_SRCS)/parsing/token.c		\
					$(DIR_SRCS)/parsing/file.c $(DIR_SRCS)/parsing/heredoc.c	\
					$(DIR_SRCS)/parsing/heredoc_rd.c							\
					$(DIR_SRCS)/parsing/sort_token.c $(DIR_SRCS)/parsing/cmd.c	\
					$(DIR_SRCS)/parsing/quotes.c $(DIR_SRCS)/parsing/quotes_utils.c\
					$(DIR_SRCS)/parsing/dollar.c								\
					$(DIR_SRCS)/parsing/check_token.c							\
					$(DIR_SRCS)/exec/exec.c	 $(DIR_SRCS)/exec/exec_util.c		\
					$(DIR_SRCS)/readline/readline.c $(DIR_SRCS)/readline/switch.c \
					$(DIR_SRCS)/signals/signal.c $(DIR_SRCS)/signals/signal_control.c

OBJS 			:= 	$(DIR_OBJS)/banner.o $(DIR_OBJS)/main.o $(DIR_OBJS)/free.o	\
					$(DIR_OBJS)/builtins/builtins.o $(DIR_OBJS)/builtins/echo.o	\
					$(DIR_OBJS)/builtins/env_utils.o $(DIR_OBJS)/builtins/env.o	\
					$(DIR_OBJS)/builtins/pwd.o $(DIR_OBJS)/builtins/cd.o		\
					$(DIR_OBJS)/builtins/export.o $(DIR_OBJS)/builtins/unset.o	\
					$(DIR_OBJS)/builtins/export_utils.o							\
					$(DIR_OBJS)/builtins/export_utils2.o 						\
					$(DIR_OBJS)/builtins/cd_path.o $(DIR_OBJS)/builtins/exit.o	\
					$(DIR_OBJS)/structs/env.o $(DIR_OBJS)/structs/env_utils.o	\
					$(DIR_OBJS)/structs/shell.o									\
					$(DIR_OBJS)/structs/history.o								\
					$(DIR_OBJS)/parsing/parse.o $(DIR_OBJS)/parsing/token.o		\
					$(DIR_OBJS)/parsing/file.o $(DIR_OBJS)/parsing/heredoc.o	\
					$(DIR_OBJS)/parsing/heredoc_rd.o							\
					$(DIR_OBJS)/parsing/sort_token.o $(DIR_OBJS)/parsing/cmd.o	\
					$(DIR_OBJS)/parsing/quotes.o $(DIR_OBJS)/parsing/quotes_utils.o\
					$(DIR_OBJS)/parsing/dollar.o								\
					$(DIR_OBJS)/parsing/check_token.o							\
					$(DIR_OBJS)/exec/exec.o	 $(DIR_OBJS)/exec/exec_util.o		\
					$(DIR_OBJS)/readline/readline.o $(DIR_OBJS)/readline/switch.o \
					$(DIR_OBJS)/signals/signal.o $(DIR_OBJS)/signals/signal_control.o

LIBFT			:= $(DIR_LIBFT)/libft.a

INCLUDES		:= -I$(DIR_LIBFT)/inc -Iinclude

all : $(LIBFT) $(NAME)

$(DIR_OBJS)/%.o: $(DIR_SRCS)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $@
	@echo "✅ Compilation completed: $(NAME)"

$(LIBFT):
	@if [ ! -f $@ ] ; then \
		$(MAKE) -s -C $(DIR_LIBFT); \
	fi

clean :
	@rm -rf $(DIR_OBJS)
	@$(MAKE) -s -C $(DIR_LIBFT) clean
	@echo "✅ clean done."

fclean : clean
	@rm -f $(NAME)
	@$(MAKE) -s -C $(DIR_LIBFT) fclean
	@echo "✅ fclean done."

re : fclean all

norm	:
	@norminette include/
	@norminette $(SRCS)

.PHONY : all clean fclean re libft
