# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ayylaaba <ayylaaba@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/03 12:04:04 by afadlane          #+#    #+#              #
#    Updated: 2023/06/06 16:26:35 by ayylaaba         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 	minishell


CFLAGS = -Wall -Wextra -Werror -I /Users/ayylaaba/.brew/Cellar/readline/8.2.1/include  #-fsanitize=address 

SRC = 	main.c \
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
		envirment.c \
		echo.c \
		get_cmd.c \
		final_utils.c \
		ft_strjoinn.c \
		ft_itoa.c \
		export_utils.c

 #OBJ = ${SRC:.c=.o}

all :${NAME} 

	
./libft/libft.a :
	@make -C ./libft

${NAME}: ./libft/libft.a ${SRC} 
	 	@cc ${CFLAGS}  ${SRC} ./libft/libft.a -L/Users/ayylaaba/.brew/Cellar/readline/8.2.1/lib  -lreadline -o ${NAME}
		
# .o : .c
# 	${cc} $(CFLAGS) -c $^ 

clean :
		@rm -f ${OBJ}

fclean : clean
		@rm -f ${NAME}
		
# rm -rf ./libft/libft.a 
nor:
	norminette

re : fclean all 
