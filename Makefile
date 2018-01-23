# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/01/22 17:11:22 by lgarczyn          #+#    #+#              #
#    Updated: 2018/01/23 21:53:09 by lgarczyn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = nm_otool

SRC =

INC = -Ilibft/includes -Iprintf
		
OBJ = $(SRC:.c=.o)

LIB = -L libft/ -lft

DEB = -g

OPT = -O2

FLG = -Wall -Wextra -Werror -funsigned-char $(OPT) $(DEB)

all: $(NAME)

$(NAME):$(OBJ) $(TEST)
	cd libft && make
	cd printf && make
	gcc -o ft_nm nm.c $(OBJS) $(INC) $(FLG) $(LIB)
	gcc -o ft_otool otool.c $(OBJS) $(INC) $(FLG) $(LIB)
	
%.o: %.c
	gcc $(INC) $(FLG) -c $< $

clean:
	rm -rf $(OBJ)
	rm -rf $(TEST)
	cd libft && make clean
	cd printf && make clean

fclean: clean
	rm -f ft_nm ft_otool
	rm -rf *.dSYM
	cd libft && make fclean
	cd printf && make fclean

re: fclean all

optire: fclean opti