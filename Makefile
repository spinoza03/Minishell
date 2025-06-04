# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/23 21:50:34 by ilallali          #+#    #+#              #
#    Updated: 2025/06/04 13:11:00 by ilallali         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = minishell

SRC = main.c execution/check_exec.c minipars.c parse_to_cmd.c utils/nodes_managemet.c builts/build_pwd.c \
	builts/check_builts.c execution/creat_env.c execution/execute_external.c execution/execution_utils.c \
	utils/nodes_2.c utils/env_utils.c func/funct1.c func/funct2.c
 
OBJ = ${SRC:.c=.o}
HEADER = include/exec.h

all: ${NAME}

${NAME}: ${OBJ}
	${CC} ${CFLAGS} ${OBJ} -lreadline -o ${NAME}

%.o: %.c ${HEADER}
	${CC} ${CFLAGS} -I include -c $< -o $@

clean:
	rm -f ${OBJ}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: clean