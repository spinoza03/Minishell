# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/23 21:50:34 by ilallali          #+#    #+#              #
#    Updated: 2025/05/26 14:31:31 by ilallali         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = 
NAME = minishell

SRC = main.c parse_to_cmd.c minipars.c

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