# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akloster <akloster@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/24 02:28:42 by akloster          #+#    #+#              #
#    Updated: 2024/11/10 19:06:14 by akloster         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RM				=	rm -rf

SRC_DIR			=	src/

SRC				=	main.c														\
					utils/ft_error.c											\
					utils/parsing.c												\
					utils/ft_mod_atoi.c											\
					utils/ft_mod_strlen.c										\
					utils/alloc_handler.c										\
					philosophing.c												\
					utils/init_philo.c											\
					utils/wrapper_fct.c

HEADERS			=	includes/philo.h

OBJ_DIR			=	objs/

OBJ				=	$(addprefix $(OBJ_DIR), $(SRC:.c=.o))

CC				=	cc

CFLAGS			=	-Iincludes -Wall -Wextra -Werror -pthread
NAME			=	philo

$(NAME):		$(OBJ_DIR) $(OBJ)  
				$(CC) $(CFLAGS) $(OBJ) -o $@

all:			$(NAME)

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c $(HEADERS)
				@mkdir -p $(dir $@)
				$(CC) $(CFLAGS) -c $< -o $@


$(OBJ_DIR):	
				@mkdir -p $(OBJ_DIR)

clean:
				$(RM) $(OBJ_DIR)

fclean:			clean
				$(RM) $(NAME) $(OBJ_DIR)

re:				fclean $(NAME)


.PHONY:			all clean fclean re
