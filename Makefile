# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: brturcio <brturcio@student.42angouleme.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/01 07:16:59 by brturcio          #+#    #+#              #
#    Updated: 2025/06/10 20:19:31 by brturcio         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= minishell
CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror -g


DIR_SRCS		:= srcs
DIR_OBJS		:= objs
DIR_LIBFT		:= libft

SRCS			:=	$(DIR_SRCS)/banner.c $(DIR_SRCS)/main.c $(DIR_SRCS)/free.c	\
					$(DIR_SRCS)/builtins/builtins.c $(DIR_SRCS)/builtins/echo.c	\
					$(DIR_SRCS)/builtins/env_utils.c $(DIR_SRCS)/builtins/env.c	\
					$(DIR_SRCS)/builtins/pwd.c $(DIR_SRCS)/builtins/cd.c		\
					$(DIR_SRCS)/builtins/export.c $(DIR_SRCS)/builtins/export_utils.c\
					$(DIR_SRCS)/builtins/export_utils2.c \
					$(DIR_SRCS)/builtins/cd_path.c $(DIR_SRCS)/builtins/exit.c	\
					$(DIR_SRCS)/builtins/unset.c 	\
					$(DIR_SRCS)/structs/env.c $(DIR_SRCS)/structs/env_utils.c\
					$(DIR_SRCS)/structs/shell.c		\
					$(DIR_SRCS)/structs/history.c								\
					$(DIR_SRCS)/parsing/parse.c $(DIR_SRCS)/parsing/token.c		\
					$(DIR_SRCS)/parsing/file.c $(DIR_SRCS)/parsing/heredoc.c	\
					$(DIR_SRCS)/parsing/sort_token.c $(DIR_SRCS)/parsing/cmd.c	\
					$(DIR_SRCS)/exec/exec.c		$(DIR_SRCS)/exec/exec_util.c			\
					$(DIR_SRCS)/readline/readline.c $(DIR_SRCS)/readline/switch.c\
					$(DIR_SRCS)/signals/signal.c $(DIR_SRCS)/signals/signal_control.c


					#$(wildcard $(DIR_SRCS)/builtins/*.c)
					#$(wildcard $(DIR_SRCS)/*.c)
					#$(wildcard $(DIR_SRCS)/structs/*.c)
					# Add other folders below if needed (e.g., parser, utils, etc.)
					# SRCS := $(shell find $(DIR_SRCS) -type f -name "*.c")

LIBS := -lreadline -lhistory -lncurses


# Object files: convert each source file path into a corresponding .o path in objs/
# For example: srcs/builtins/echo.c → objs/builtins/echo.o
OBJS 			:= $(patsubst %.c, $(DIR_OBJS)/%.o, $(subst $(DIR_SRCS)/,,$(SRCS)))
LIBFT			:= $(DIR_LIBFT)/libft.a

# Include paths for headers (local and from libft)
INCLUDES		:= -I$(DIR_LIBFT)/inc -Iinclude

all : $(LIBFT) $(NAME)

# Compile each .c file into a .o file
# Also creates necessary subdirectories inside objs/ automatically
$(DIR_OBJS)/%.o: $(DIR_SRCS)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Link all object files with libft to produce the final executable
$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $@ $(LIBS)
	@echo "✅ Compilation completed: $(NAME)"

# Build libft only if libft.a does not already exist
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
