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

SRC = tools.c nm_disp.c swap.c headers.c parsing.c types.c ranlib.c read.c display.c

INC = -Ilibft/includes -Iprintf/includes
		
OBJ = $(addprefix obj/, $(addsuffix .o, $(basename $(SRC))))

LIB = -L libft -lft -L printf -lftprintf

DEB = #-g3 -fsanitize=address 

OPT = -O2 -march=native

FLG = -Wall -Wextra -Werror -funsigned-char -fno-signed-char -m64 $(OPT) #$(DEB)

all: $(NAME)

$(NAME):libft/libft.a printf/libftprintf.a ft_nm ft_otool

libft/libft.a:
	cd libft && make

printf/libftprintf.a:
	cd printf && make

ft_nm:$(OBJ) obj/nm.o
	@mkdir -p obj
	gcc -o ft_nm obj/nm.o $(OBJ) $(INC) $(FLG) $(LIB)

ft_otool:$(OBJ) obj/otool.o
	@mkdir -p obj
	gcc -o ft_otool obj/otool.o $(OBJ) $(INC) $(FLG) $(LIB)
	
obj/%.o: src/%.c
	@mkdir -p obj
	gcc  -o $@ -c $< $(INC) $(FLG)

lib:
	rm -rf $(OBJ) obj/nm.o obj/otool.o
	rm -f ft_nm ft_otool
	rm -rf *.dSYM

clean:
	rm -rf $(OBJ) obj/nm.o obj/otool.o
	cd libft && make clean
	cd printf && make clean

fclean: lib
	rm -f ft_nm ft_otool
	rm -rf *.dSYM
	cd libft && make fclean
	cd printf && make fclean

re: fclean all

libre: lib all

optire: fclean opti