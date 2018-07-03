#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: otiniako <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/02 16:17:52 by otiniako          #+#    #+#              #
#    Updated: 2018/07/02 16:17:53 by otiniako         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = ft_ssl

HEADER = ft_ssl.h

FLAGS = -I includes/

LIB = libft/libft.a

SRC = ft_ssl.c\
		ft_md5.c\
		ft_sha256.c\

OBJ = $(SRC:.c=.o)

all: $(LIB) $(NAME)

$(LIB):
	@make -C libft/

$(NAME): $(OBJ)
	@gcc -o $(NAME) $(OBJ) $(LIB)
	@echo "\033[1;92mft_ssl are created!\033[1;92m"

$(OBJ): %.o: %.c
	@gcc -c $(FLAGS) -o $@ -c $<

clean:
	@make -C libft/ clean
	@rm -f $(OBJ)

fclean: clean
	@rm -rf $(NAME)
	@make -C libft/ fclean

re: fclean all