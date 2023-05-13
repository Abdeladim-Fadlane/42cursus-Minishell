# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afadlane <afadlane@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/03 12:04:04 by afadlane          #+#    #+#              #
#    Updated: 2023/05/14 00:12:04 by afadlane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = 	minishell

CFLAGS = -Wall -Werror -Wextra  #-fsanitize=address -g3

SRC =  main.c \
		get_next_line.c \
		built_in.c \
		minishell_utills.c\
 		bonus_libft.c \
		deatch_redirc.c \
		ft_split_parse.c \
		redirections.c \
		minishell.c \
		parsing.c \
		utils_2.c \
		utils_3.c \
		utils_4.c \
		utils.c \
		cmd_list.c \

#OBJ = ${SRC:.c=.o}

all :${NAME} 

run : ${NAME}
		@./${NAME} 
		
./libft/libft.a :
	@make -C ./libft

${NAME}: ./libft/libft.a ${SRC} 
	 	@cc ${CFLAGS} ${SRC} ./libft/libft.a -lreadline -o ${NAME}
clean :
		@rm -f ${OBJ} 

fclean : clean
		@rm -f ${NAME}

nor:
	norminette

re : fclean all 
