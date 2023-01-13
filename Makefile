NAME = minishell

CC = gcc
CFLAGS = -g3

SRCPATH = src/
SRC = main.c \
		libft.c	\
		split.c \
		supp.c \
		free.c \
		quote.c \
		find_commande.c \
		find_input_output.c \
		clean_split_arg.c \
		create_maillons.c \
		split_list.c \
		list_split_elem.c \
		list_input_output.c \
		parsing.c  \
		utils_zak.c  \
		garbage_collector.c \
		signals.c\
		replace_dollar.c\
		clear_maillons.c \
		list_maillons.c \
		parsing_input.c \
		pipex.c \


BUILTIN_SRC = builtin/builtin_echo.c \
				builtin/builtin_cd.c  \
				builtin/builtin_pwd.c \
				builtin/builtin_env.c  \
				builtin/builtin_export.c  \
				builtin/builtin_exit.c  \
				builtin/builtin_unset.c

PIPEX_SRC = pipe_of_zak/pipe_de_2.c \
				pipe_of_zak/security.c  \
				pipe_of_zak/utils_pipex.c \
				pipe_of_zak/utils_pipex_2.c  \
				

OBJ = $(SRC:.c=.o) $(BUILTIN_SRC:.c=.o) $(PIPEX_SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	@echo "\033[36mMaking Minishell \033[0m"
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -lreadline
	@echo "\033[32mDone\033[0m"

%.o : $(SRCPATH)%.c
	@$(CC) $(CFLAGS) -c $^ 

%.o : $(SRCPATH)builtin/%.c
	@$(CC) $(CFLAGS) -c $^

%.o : $(SRCPATH)pipe_of_zak/%.c
	@$(CC) $(CFLAGS) -c $^
bonus : all

clean :
	@echo "\033[35mCleaning Minishell objects...\033[0m"
	@rm -f $(OBJ)
	@echo "\033[32mDone\033[0m"

fclean : clean
	@echo "\033[35mCleaning  Minishell...\033[0m"
	@rm -f $(NAME)
	@echo "\033[32mDone\033[0m"

re : fclean
	make all

.PHONY : all clean fclean re bonus