# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/14 17:58:20 by vlugand-          #+#    #+#              #
#    Updated: 2021/07/08 17:44:08 by vlugand-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		=	philo_one

SRCS		=	srcs/init.c\
				srcs/life.c\
				srcs/logs.c\
				srcs/main.c\
				srcs/threads.c\
				srcs/time.c\
				srcs/utils.c

CC			= 	gcc
OBJS		= 	${SRCS:.c=.o}
CFLAGS		= 	-Wall -Wextra -Werror
RM			= 	rm -f

all:		${NAME}

.c.o:
			${CC} ${CFLAGS} -I includes -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
			${CC} ${CFLAGS} ${OBJS} -o ${NAME}
			@echo "\033[0;32m\033[1mphilo_one is now ready!\033[0m"
			@echo ""
			@echo "\033[92m██████  ██   ██ ██ ██       ██████  ███████  ██████  ██████  ██   ██ ███████ ██████  ███████ "
			@echo "\033[93m██   ██ ██   ██ ██ ██      ██    ██ ██      ██    ██ ██   ██ ██   ██ ██      ██   ██ ██      "
			@echo "\033[91m██████  ███████ ██ ██      ██    ██ ███████ ██    ██ ██████  ███████ █████   ██████  ███████ "
			@echo "\033[95m██      ██   ██ ██ ██      ██    ██      ██ ██    ██ ██      ██   ██ ██      ██   ██      ██ "
			@echo "\033[96m██      ██   ██ ██ ███████  ██████  ███████  ██████  ██      ██   ██ ███████ ██   ██ ███████  \033[0mby vlugand-"
			@echo ""

clean:
			${RM} ${OBJS}
			@echo "\033[0;35m\033[1mCleaned all .o files.\033[0m"

fclean:
			${RM} ${OBJS}
			${RM} ${NAME}
			@echo "\033[0;35m\033[1mCleaned all .o files and executable.\033[0m"

re:			fclean all

.PHONY:		all clean fclean re bonus
