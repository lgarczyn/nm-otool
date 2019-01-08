# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/05/06 14:07:52 by lgarczyn          #+#    #+#              #
#    Updated: 2019/01/08 19:06:16 by lgarczyn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

DEB = #-g3 -fsanitize=address

OPT = -O2 -march=native

FLAGS = -Wall -Wextra -Werror -funsigned-char -fno-signed-char  $(OPT)

INCLUDES = includes

CC = gcc

SRC = ft_atoi.c \
	  ft_bzero.c \
	  ft_intlen.c \
	  ft_isalnum.c \
	  ft_isalpha.c \
	  ft_isascii.c \
	  ft_isdigit.c \
	  ft_isempty.c \
	  ft_isprint.c \
	  ft_isspace.c \
	  ft_itoa.c \
	  ft_lstadd.c \
	  ft_lstdel.c \
	  ft_lstdelone.c \
	  ft_lstiter.c \
	  ft_lstmap.c \
	  ft_lstnew.c \
	  ft_memalloc.c \
	  ft_memccpy.c \
	  ft_memchr.c \
	  ft_memcmp.c \
	  ft_memcpy.c \
	  ft_memdel.c \
	  ft_memmove.c \
	  ft_memset.c \
	  ft_putchar.c \
	  ft_putchar_fd.c \
	  ft_putendl.c \
	  ft_putendl_fd.c \
	  ft_putnbr.c \
	  ft_putnbr_fd.c \
	  ft_putnstr.c \
	  ft_putnstr_fd.c \
	  ft_putspace.c \
	  ft_putstr.c \
	  ft_putstr_fd.c \
	  ft_realloc.c \
	  ft_strcat.c \
	  ft_strchr.c \
	  ft_strclr.c \
	  ft_strcmp.c \
	  ft_strcmp_fast.c \
	  ft_strcpy.c \
	  ft_strdel.c \
	  ft_strdup.c \
	  ft_strdupwhile.c \
	  ft_strequ.c \
	  ft_striter.c \
	  ft_striteri.c \
	  ft_strjoin.c \
	  ft_strlcat.c \
	  ft_strlen.c \
	  ft_wstrlen.c \
	  ft_strlen_fast.c \
	  ft_strmap.c \
	  ft_strmapi.c \
	  ft_strncat.c \
	  ft_strncmp.c \
	  ft_strncpy.c \
	  ft_strnequ.c \
	  ft_strnew.c \
	  ft_strnstr.c \
	  ft_strrchr.c \
	  ft_strsplit.c \
	  ft_strstr.c \
	  ft_strsub.c \
	  ft_strtrim.c \
	  ft_tolower.c \
	  ft_toupper.c \
	  ft_buf.c \
	  ft_flush_buf.c \
	  ft_flush_total.c \
	  ft_flush_overflow.c \
	  ft_get_buf.c \
	  ft_putchar_buf.c \
	  ft_putnchar_buf.c \
	  ft_putwchar_buf.c \
	  ft_putendl_buf.c \
	  ft_putnendl_buf.c \
	  ft_putnbr_buf.c \
	  ft_putnendl_buf.c \
	  ft_putspace_buf.c \
	  ft_putnstr_buf.c \
	  ft_putmstr_buf.c \
	  ft_putstr_buf.c \
	  ft_putnwstr_buf.c \
	  ft_putwstr_buf.c \
	  ft_putrnstr_buf.c \
	  ft_putrstr_buf.c \
	  ft_reset_buf.c \
	  ft_setfd_buf.c \
	  ft_perror.c \
	  ft_strerror.c \

RM = rm -f

OBJ = $(addprefix obj/, $(addsuffix .o, $(basename $(SRC))))

all: $(NAME)

obj/%.o: src/%.c
	@mkdir -p obj
	$(CC) -o $@ -c $< $(FLAGS) -I $(INCLUDES)

$(NAME) : $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all
