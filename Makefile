SOURCES = main.c built-in/env.c  built-in/pwd.c lexer/lexer.c \
			lexer/lexer_3.c lexer/lexer_utils.c lexer/lexer_quotes.c \
			parser/parser_1.c parser/parser.c parser/parser_utils.c \
			lexer/dollar_lexer.c parser/double_quotes.c parser/env_parsing.c \
			exec/exec_utils.c exec/pipe.c exec/check_command.c exec/ft_free_all.c \
			exec/redirection.c exec/redirect_utils.c exec/heredoc.c built-in/echo.c \
			built-in/ft_built_in.c built-in/ft_cd.c built-in/unset.c built-in/ft_exit.c \
			built-in/export.c built-in/export_2.c exec/check_command_2.c exec/heredoc_2.c \
			exec/pipe_2.c handlers.c exec/pipe_3.c \
			libft/ft_atoi.c libft/ft_calloc.c libft/ft_isalnum.c libft/ft_isalpha.c \
			libft/ft_isdigit.c libft/ft_printf/srcs/ft_printf.c libft/ft_itoa.c \
			libft/ft_putchar_fd.c libft/ft_split.c libft/ft_strchr.c libft/ft_strdup.c \
			libft/ft_strjoin.c libft/ft_strlcat.c libft/ft_strlcpy.c libft/ft_strlen.c \
			libft/ft_strncmp.c libft/ft_strrchr.c libft/ft_strnstr.c libft/ft_putstr_fd.c \
			libft/ft_bzero.c libft/ft_printf/srcs/ft_printf_utils.c libft/ft_printf/srcs/print_args.c \
			libft/ft_printf/srcs/print_hexa.c libft/ft_printf/srcs/print_ptr.c \
			libft/ft_printf/srcs/print_unsigned_int.c libft/ft_printf/srcs/ft_putstr.c
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

all : $(NAME) 

$(NAME): ${OBJS}
	@${CC} -o $(NAME) $(OBJS) ${FLAGS}
	@echo "${YELLOW}successfully created minishell!${END}"

.c.o:
	@${CC} ${FLAGS} -c $< -o ${<:.c=.o}

clean:
	@${RM} ${OBJS}

fclean: clean
	@${RM} ${NAME}
	@echo "${ORANGE}removing all .o files from minishell...${END}"

re: fclean all

.PHONY: all, clean, fclean, re

.SILENT: all clean fclean 