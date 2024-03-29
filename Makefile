# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jrasser <jrasser@student.42mulhouse.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/17 05:26:46 by jrasser           #+#    #+#              #
#    Updated: 2023/09/01 23:29:22 by jrasser          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= srcs/main.c \
			\
			srcs/parse/parsing.c  \
			srcs/parse/ft_split_and_omit.c  \
			srcs/parse/ft_strjoin_andadd_rt.c  \
			srcs/parse/redirection.c \
			srcs/parse/redirection2.c \
			srcs/parse/redirection3.c \
			srcs/parse/determining_type_redir.c \
			srcs/parse/ft_split_redirection.c \
			srcs/parse/ft_replace_elements.c \
			srcs/parse/list_utils.c \
			srcs/parse/parsing_utils.c \
			srcs/parse/parsing_utils2.c \
			srcs/parse/parsing_utils3.c \
			srcs/parse/replace_var.c \
			srcs/parse/ft_delete_elements.c \
			srcs/parse/termcap.c \
			\
			srcs/execution/pipe.c \
			srcs/execution/pipe_checker.c\
			srcs/execution/checker_access.c\
			srcs/execution/utils_pipe.c \
			srcs/execution/handle_error.c \
			srcs/execution/free.c \
			srcs/execution/prompt.c \
			srcs/execution/heredoc.c \
			srcs/execution/builtins/builtins1.c \
			srcs/execution/builtins/exit.c \
			srcs/execution/builtins/env.c \
			srcs/execution/builtins/export.c \
			srcs/execution/builtins/unset.c \

OBJS 		= ${SRCS:.c=.o}
RM			= @rm -f
NAME 		= minishell
CC			= gcc
CFLAGS		= -Wall -Wextra
LDFLAGS		= -I./include/ -I./libft/ -I/Users/ydumaine/.brew/opt/readline/include
DEBEUG		= -fsanitize=address

.c.o:		
			@${CC} -g ${CFLAGS} -c ${LDFLAGS} $< -o ${<:.c=.o}

${NAME}	:	${OBJS}
			$(MAKE) --no-print-directory -C ./libft
			gcc -o ${NAME} ${OBJS} -g -lreadline -L/Users/ydumaine/.brew/opt/readline/lib -L./libft -lft

all :		${NAME}


clean :
			${RM} ${OBJS}

fclean :	clean
			${RM} ${NAME}
			@make --no-print-directory fclean -C libft/

re : 		fclean all

.PHONY:		all clean fclean re
