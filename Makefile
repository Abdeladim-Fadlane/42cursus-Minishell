# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afadlane <afadlane@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/03 12:04:04 by afadlane          #+#    #+#              #
#    Updated: 2023/05/24 21:46:50 by afadlane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = 	minishell

CFLAGS = -Wall -Wextra -Werror -I/Users/afadlane/Desktop/readline/8.2.1/include/  -fsanitize=address 

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
		built_in_utils.c \
		exucution.c \
		exutcutin_utils.c \
		export.c \
		libft_bonus.c \
		utils_built_in.c \

#OBJ = ${SRC:.c=.o}

all :${NAME} 

run : ${NAME}
		@./${NAME} 
		
./libft/libft.a :
	@make -C ./libft

${NAME}: ./libft/libft.a ${SRC} 
	 	@cc ${CFLAGS} ${SRC} ./libft/libft.a  -L/Users/afadlane/Desktop/readline/8.2.1/lib/ -lreadline   -o ${NAME}
clean :
		@rm -f ${OBJ} 

fclean : clean
		@rm -f ${NAME}

nor:
	norminette

re : fclean all 
