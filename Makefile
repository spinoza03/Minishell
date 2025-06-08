
CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = minishell

SRC = main.c execution/check_exec.c minipars.c parse_to_cmd.c utils/nodes_managemet.c builts/build_pwd.c \
	builts/check_builts.c execution/creat_env.c execution/execute_external.c execution/execution_utils.c \
	utils/nodes_2.c utils/env_utils.c func/funct1.c func/funct2.c func/funct3.c builts/build_echo.c

OBJ = ${SRC:.c=.o}
HEADER = include/exec.h

define STYLISH_MESSAGE
@echo -e "\n\033[1;35m********************************************************************************"
@echo -e "* *"
@echo -e "* \033[1;36m __  __ _       _ __          _ _ \033[1;35m                                  *"
@echo -e "* \033[1;36m|  \\/  (_)     (_)_ |        | | |\033[1;35m                                  *"
@echo -e "* \033[1;36m| \\  / |_ _ __  _ _| | ___  __| | |\033[1;35m  Welcome to Minishell!         *"
@echo -e "* \033[1;36m| |\\/| | | '_ \\| | | |/ _ \\/ _\` | |\033[1;35m  Compiling your shell...       *"
@echo -e "* \033[1;36m| |  | | | | | | | | |  __/ (_| |_|\033[1;35m                                  *"
@echo -e "* \033[1;36m|_|  |_|_|_| |_|_|_|_|\\___|\\__,_(_)\033[1;35m                                  *"
@echo -e "* *"
@echo -e "\033[1;35m********************************************************************************\033[0m\n"
endef

all: print_message ${NAME}

print_message:
	$(STYLISH_MESSAGE)

${NAME}: ${OBJ}
	@echo -e "\033[0;32mLinking objects to create ${NAME}...\033[0m"
	${CC} ${CFLAGS} ${OBJ} -lreadline -o ${NAME}
	@echo -e "\033[1;32mSuccessfully compiled ${NAME}!\033[0m"

%.o: %.c ${HEADER}
	@echo -e "\033[0;33mCompiling $<...\033[0m"
	${CC} ${CFLAGS} -I include -c $< -o $@

clean:
	@echo -e "\033[0;31mCleaning object files...\033[0m"
	rm -f ${OBJ}
	@echo -e "\033[1;32mObject files cleaned.\033[0m"

fclean: clean
	@echo -e "\033[0;31mCleaning ${NAME} executable...\033[0m"
	rm -f ${NAME}
	@echo -e "\033[1;32m${NAME} executable cleaned.\033[0m"

re: fclean all

.PHONY: clean fclean re print_message