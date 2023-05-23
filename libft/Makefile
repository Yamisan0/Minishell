# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: imessaad <imessaad@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/17 12:21:25 by imessaad          #+#    #+#              #
#    Updated: 2023/03/01 13:58:43 by imessaad         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRCS = ft_atoi.c ft_isdigit.c ft_strlcpy.c ft_toupper.c \
	ft_bzero.c ft_isprint.c ft_strlen.c ft_calloc.c \
	ft_memchr.c ft_strchr.c ft_strncmp.c ft_isalnum.c \
	ft_memcmp.c ft_strdup.c ft_strnstr.c ft_isalpha.c \
	ft_memcpy.c ft_strjoin.c ft_strrchr.c ft_isascii.c \
	ft_memmove.c ft_strlcat.c  ft_tolower.c \
	ft_strmapi.c ft_substr.c ft_strjoin.c ft_strtrim.c \
	ft_itoa.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
	ft_putendl_fd.c ft_putnbr_fd.c ft_split.c ft_memset.c \
	get_next_line/get_next_line.c ft_printf/srcs/ft_printf_utils.c \
	ft_printf/srcs/ft_printf.c ft_printf/srcs/ft_putstr.c \
	ft_printf/srcs/print_args.c ft_printf/srcs/print_hexa.c \
	ft_printf/srcs/print_ptr.c ft_printf/srcs/print_unsigned_int.c 

BONUS = ft_lstnew.c ft_lstdelone.c ft_lstclear.c \
		ft_lstadd_front.c ft_lstadd_back.c ft_lstsize.c \
		ft_lstiter.c ft_lstmap.c ft_lstlast.c
CC = clang
CFLAGS = -Wall -Werror -Wextra -g3
RM = rm -f
OBJS = ${SRCS:.c=.o}

BONUS_OBJS = ${BONUS:.c=.o}
NAME = libft.a

#Colors

GREY=\033[0;37m
RED=\033[0;31m
GREEN= \033[92m
YELLOW=\033[1;33m
BLUE=\033[0;34m
PURPLE=\033[0;35m
ORANGE = \033[0;33m
CYAN=\033[0;36m
WHITE=\033[1;37m
END=\033[0m

all : ${NAME} bonus

$(NAME) : ${OBJS}
	@ar rcs ${NAME} ${OBJS}
	@echo "${GREEN}Creating libft.a ...${END}"

.c.o:
	@${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

clean:
	${RM} ${OBJS} ${BONUS_OBJS}

fclean: clean
	@${RM} ${NAME}
	@echo "${PURPLE}removing all files .o files from libft ...${END}"

re: fclean all

bonus: ${BONUS_OBJS}
	ar rcs ${NAME} ${BONUS_OBJS}

.PHONY: all, clean, fclean, re

.SILENT: all clean fclean re bonus