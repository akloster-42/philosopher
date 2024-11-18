# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akloster <akloster@student.s19.be>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/24 02:28:42 by akloster          #+#    #+#              #
#    Updated: 2024/11/18 16:33:37 by akloster         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RM				=	rm -rf

SRC_DIR			=	src/

SRC				=	main.c														\
					utils/parsing.c												\
					utils/tools.c										\
					utils/alloc_handler.c										\
					philosophing.c												\
					utils/init_philo.c											\
					utils/wrapper_fct.c											\
					utils/time_keeping.c										\
					utils/philo_actions.c

HEADERS			=	includes/philo.h

OBJ_DIR			=	objs/

OBJ				=	$(addprefix $(OBJ_DIR), $(SRC:.c=.o))

CC				=	cc

CFLAGS			=	-Iincludes -Wall -Wextra -Werror -pthread #-g -fsanitize=thread

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
