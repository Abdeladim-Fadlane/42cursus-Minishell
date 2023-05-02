# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afadlane <afadlane@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/03 12:04:04 by afadlane          #+#    #+#              #
#    Updated: 2023/05/02 20:34:54 by afadlane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = 	Minishell

CFLAGS = -Wall -Werror -Wextra   -fsanitize=address  -g3

SRC =  main.c  minishell_utills.c get_next_line.c libft.c minishell.c

cc = cc
#OBJ = ${SRC:.c=.o}

all :${NAME}

run : ${NAME}
		@./${NAME} 
		
./libft/libft.a :
	@make -C ./libft

${NAME}: ./libft/libft.a ${SRC} 
	 	@${cc} ${CFLAGS} ${SRC} ./libft/libft.a -lreadline -o ${NAME}

clean :
		@rm -f ${OBJ} 

fclean : clean
		@rm -f ${NAME} 

nor:
	norminette

re : fclean all 
