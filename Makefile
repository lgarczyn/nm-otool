# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/01/22 17:11:22 by lgarczyn          #+#    #+#              #
#    Updated: 2018/01/26 00:20:12 by lgarczyn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = nm_otool

SRC = tools.c swap.c

INC = -Ilibft/includes -Iprintf
		
OBJ = $(SRC:.c=.o)

LIB = -L libft/ -lft #-L printf -lftprintf

DEB = 

OPT = -O2

FLG = -Wall -Wextra -Werror -funsigned-char  -m64 $(OPT) $(DEB)

all: $(NAME)

$(NAME):$(OBJ)
	cd libft && make
	cd printf && make
	gcc -o ft_nm nm.c $(OBJ) $(INC) $(FLG) $(LIB)
	#gcc -o ft_otool otool.c $(OBJ) $(INC) $(FLG) $(LIB)
	
%.o: %.c
	gcc $(INC) $(FLG) -c $< $

h:
	rm -rf $(OBJ)
	rm -f ft_nm ft_otool
	rm -rf *.dSYM

clean:
	rm -rf $(OBJ)
	cd libft && make clean
	cd printf && make clean

fclean: h
	rm -f ft_nm ft_otool
	rm -rf *.dSYM
	cd libft && make fclean
	cd printf && make fclean

re: fclean all

hre: h all

optire: fclean opti