

NAME = minishell
CC = cc
RM = rm -f
CFLAGS = -I includes -g -MMD -MP -Wall -Wextra -Werror 
LDFLAGS = -lreadline

# Directories
LIBFT_DR = libft
SRC_DIR = .
OBJ_DIR = obj

# Source Files
SRCS =	main.c \
        signals/ft_signals.c \
        utils/ft_get_prompt.c \
		utils/ft_utils.c\
		utils/ft_lst_utils.c \
		lexer/ft_start_check.c \
		lexer/ft_token.c \
		lexer/ft_start.c \
		lexer/ft_grammar.c \
		lexer/ft_quotes.c \
		lexer/ft_expand.c \
		lexer/ft_expand_2.c \
		lexer/ft_expand_3.c \
		parser/ft_parsing.c \
		parser/ft_redirections.c \
		parser/ft_word_var.c \
		parser/ft_heredoc.c \
		exit_error/ft_freedom.c \
		exit_error/ft_exit_pipe.c \
		exit_error/ft_lst_cmd_exit.c \
		exit_error/ft_lst_env_exit.c \
		exit_error/ft_lst_tok_exit.c \
		exit_error/ft_messaging.c \
		env/ft_envar.c \
		env/ft_env_array.c \
		env/ft_env_special.c \
		execution/ft_builtin_trigger.c \
		execution/ft_fdhandle.c \
		execution/ft_pathfind.c \
		execution/ft_execution.c \
		execution/ft_execution_2.c \
		data_init/ft_data_init.c \
		data_init/ft_displays.c \
		data_init/ft_struct_init_file.c \
		data_init/ft_lst_cmd_init.c \
		data_init/ft_lst_env_init.c \
		data_init/ft_lst_tok_init.c \
		built_ins/ft_unset.c \
		built_ins/ft_env.c \
		built_ins/ft_pwd.c \
		built_ins/ft_export.c \
		built_ins/ft_export_utils.c \
		built_ins/ft_cd.c \
		built_ins/ft_exit.c \
		built_ins/ft_echo.c \
		
# Generate object files in OBJ_DIR
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

# Libraries
LIBFT = $(LIBFT_DR)/libft.a

# Include paths
INCLUDES = -I. -I$(LIBFT_DR)

HEADER = minishell.h

all: $(OBJ_DIR) $(LIBFT) $(NAME)

# Create object directory
$(OBJ_DIR):
	@if [ ! -d $(OBJ_DIR) ]; then \
		mkdir -p $(OBJ_DIR); \
		echo "Created object directories"; \
	fi

# Build Libraries
$(LIBFT):
	@if [ ! -f "$(LIBFT)" ]; then \
		echo "Built libft"; \
		make --no-print-directory -C $(LIBFT_DR); \
	fi

# Link everything
$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -L$(LIBFT_DR) -lft -o $(NAME)
	@echo "Built everything for minishell"

# Compile objects
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) -r $(OBJ_DIR)
	@make -C $(LIBFT_DR) clean
	@echo "Cleaned object files"

fclean: clean
	$(RM) $(NAME)
	@make -C $(LIBFT_DR) fclean
	@echo "Cleaned executable files"

re: fclean all

.PHONY: all clean fclean re $(OBJ_DIR)
