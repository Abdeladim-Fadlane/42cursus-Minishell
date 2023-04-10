# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afadlane <afadlane@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/03 12:04:04 by afadlane          #+#    #+#              #
#    Updated: 2023/04/07 17:54:45 by afadlane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 	Minishell

CFLAGS = -Wall -Werror -Wextra   #-fsanitize=address 

SRC = minishell.c main.c  minishell_utills.c get_next_line.c
	
cc = gcc
#OBJ = ${SRC:.c=.o}

all :${NAME}

run : ${NAME}
		@./${NAME} 
		
${NAME}: ${SRC} 
	 	${cc} ${CFLAGS} ${SRC} -lreadline -o ${NAME}


clean :
		rm -f ${OBJ} 

fclean : clean
		rm -f ${NAME} 

nor:
	norminette

re : fclean all 
