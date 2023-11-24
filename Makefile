# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nachab <nachab@student.1337.ma>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/19 17:11:40 by nachab            #+#    #+#              #
#    Updated: 2023/06/19 17:14:44 by nachab           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = mainMinishell/minishell.c mainMinishell/listComand.c mainMinishell/export.c mainMinishell/export2.c mainMinishell/export3.c mainMinishell/minishellPart2.c mainMinishell/minishellPart3.c  mainMinishell/listFiles.c outilsFunctions/signal_handler.c outilsFunctions/heredoc_utils.c outilsFunctions/ft_putnbr_fd.c outilsFunctions/ft_putchar_fd.c outilsFunctions/ft_itoa.c outilsFunctions/ft_strnstr.c outilsFunctions/ft_strncmp.c outilsFunctions/my_strjoin.c outilsFunctions/exit_utils.c outilsFunctions/check_if_number.c outilsFunctions/ft_putstr_fd.c outilsFunctions/ft_calloc.c outilsFunctions/ft_strlen.c outilsFunctions/ft_strcat.c outilsFunctions/ft_strchr.c outilsFunctions/ft_strjoin.c outilsFunctions/ft_strjoin2.c outilsFunctions/ft_strchr2.c  outilsFunctions/ft_strcpy.c outilsFunctions/ft_split.c outilsFunctions/ft_strcmp.c outilsFunctions/ft_substr.c listEnvp/listEnvp.c listEnvp/listEnvpFree.c lexer/lexer.c lexer/lexer2.c lexer/lexer3.c lexer/lexer4.c lexer/lexer5.c  lexer/lexer6.c lexer/lexer7.c lexer/listLexer.c lexer/outilLexer.c outilsFunctions/ft_strdup.c parser/checkSyntax.c parser/checkSyntax2.c parser/checkSyntax3.c expand/expandVariable.c expand/expandVariable2.c expand/expandVariable3.c organizComands/organizComands.c organizComands/organizComands2.c organizComands/organizComands3.c organizComands/organizComands4.c organizComands/organizComands5.c organizComands/organizComands6.c organizComands/organizComands7.c execution/get_cmd_path.c execution/handle_streams.c execution/heredoc.c execution/update_env.c  execution/pipes.c execution/single_cmd.c execution/handle_cmd.c  builtins/child_builtin.c builtins/exit.c builtins/parent_builtin.c builtins/echo.c builtins/pwd.c builtins/cd.c

RDL_DIR = -L /goinfre/nachab/.brew/opt/readline/lib -I /goinfre/nachab/.brew/opt/readline/include/readline -lreadline 

FLAGS = -Wall -Werror -Wextra

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@cc -o $@ $(FLAGS) $(RDL_DIR) $^
	@echo "\033[32m** CREATED MINISHELL **\033[9m"

%.o: %.c
	@cc $(FLAGS) -c $< -o $@

clean:
	@find . -type f -name "*.o" -delete

fclean: clean
	@rm -f $(NAME) a.out *.txt

re: fclean all

.PHONY: all clean fclean re
