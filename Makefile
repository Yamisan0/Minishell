SOURCES = main.c built-in/env.c  built-in/pwd.c lexer/lexer.c \
			lexer/lexer_2.c
LIB_PATH = libft
#compilation
CC		= gcc
FLAGS	= -Wall -Wextra -Werror -g3 -lreadline

RM = rm -f
LIB_PATH_EXEC = libft/libft.a

#executable
NAME = minishell

#colors

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


#creation objects
OBJS = $(SOURCES:.c=.o)

all : libft_make $(NAME) 

$(NAME): ${OBJS}
	@${CC} -o $(NAME) $(OBJS) $(LIB_PATH_EXEC) ${FLAGS}
	@echo "${YELLOW}successfully created minishell!${END}"

.c.o:
	@${CC} ${FLAGS} -c $< -o ${<:.c=.o}

clean: libft_fclean
	@${RM} ${OBJS}

fclean: clean
	@${RM} ${NAME}
	@echo "${ORANGE}removing all .o files from minishell...${END}"

libft_make: 
	@cd $(LIB_PATH); make; cd ..

libft_fclean:
	@cd $(LIB_PATH); make fclean; cd ..

re: fclean all

.PHONY: all, clean, fclean, re

.SILENT: all clean fclean 