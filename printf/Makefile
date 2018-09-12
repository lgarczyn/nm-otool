# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/01/22 17:11:22 by lgarczyn          #+#    #+#              #
#    Updated: 2018/01/25 22:04:50 by lgarczyn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRC =	printf.c \
		display.c \
		display_text.c \
		display_int.c \
		wrappers.c

INC = ../libft/includes
		
OBJ = $(addprefix obj/, $(addsuffix .o, $(basename $(SRC))))

LIB = -L ../libft/ -lft

DEB = -g3 -fsanitize=address

OPT = -O0

FLG = -Wall -Wextra -Werror -funsigned-char $(OPT) $(DEB)

all: $(NAME)

$(NAME):$(OBJ) $(TEST)
	ar rcs $(NAME) $(OBJ)
	
obj/%.o: src/%.c
	@mkdir -p obj
	gcc -o $@ -c $< -I$(INC) $(FLG)

clean:
	rm -f $(OBJ)
	rm -f $(TEST)

fclean: clean
	rm -f $(NAME)
	rm -f $(TNAME)

re: fclean all

optire: fclean opti