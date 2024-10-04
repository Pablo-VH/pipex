NAME        	= pipex
NAME_BONUS		= checker
CC          	= gcc
CFLAGS      	= -Wextra -Werror -Wall -I$(INC) -I$(LIBFT_DIR)inc/ -I$(PRINTF_DIR)inc/
#-g3 -fsanitize=address 
LDFLAGS     	= -L$(LIBFT_DIR) -lft -L$(PRINTF_DIR) $(PRINTF) -lftprintf

INC         	= inc/

LIBFT_DIR   	= libft/
LIBFT       	= $(LIBFT_DIR)libft.a

PRINTF_DIR		= ft_printf/
PRINTF			= $(PRINTF_DIR)libftprintf.a

SRCS_DIR    	= srcs/
OBJS_DIR    	= objs/
SRCS_FILES		= pipex.c utils.c \
				
	
BONUS_DIR    	= srcs_bonus/
OBJS_BONUS_DIR	= objs_bonus/
BONUS_FILES		= call_inst.c check_errors.c instructions.c main.c utils.c check_errors2.c \

OBJS_FILES			= $(SRCS_FILES:.c=.o)

OBJS_BONUS_FILES	= $(BONUS_FILES:.c=.o)

SRCS		= $(addprefix $(SRCS_DIR), $(SRCS_FILES))
OBJS		= $(addprefix $(OBJS_DIR), $(OBJS_FILES))

SRCS_BONUS	= $(addprefix $(BONUS_DIR), $(BONUS_FILES))
OBJS_BONUS	= $(addprefix $(OBJS_BONUS_DIR), $(OBJS_BONUS_FILES))

all: $(NAME)

$(NAME): $(LIBFT) $(PRINTF) $(OBJS) 
	@echo "\nCompiling $(BLUE)$(NAME)$(DEF_COLOR)"
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)
	@echo "\n$(GREEN)$(NAME) compiled!$(DEF_COLOR)"
	@echo "$(BOLD_CYAN)\n------------\n| Done! 👌 |\n------------$(DEF_COLOR)"

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@[ -d $(OBJS_DIR) ] || mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_BONUS_DIR)%.o: $(BONUS_DIR)%.c
	@[ -d $(OBJS_BONUS_DIR) ] || mkdir -p $(OBJS_BONUS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@echo "\nCompiling $(BLUE)libft$(DEF_COLOR)"
	@make -sC $(LIBFT_DIR)


$(PRINTF):
	@echo "\nCompiling $(BLUE)printf$(DEF_COLOR)"
	@make -sC $(PRINTF_DIR)

bonus: $(LIBFT) $(PRINTF) $(OBJS_BONUS) 
	@echo "\nCompiling $(BLUE)$(NAME_BONUS)$(DEF_COLOR)"
	@$(CC) $(CFLAGS) $(OBJS_BONUS) $(LDFLAGS) -o $(NAME_BONUS)
	@echo "\n$(GREEN)$(NAME_BONUS) compiled!$(DEF_COLOR)"
	@echo "$(BOLD_CYAN)\n------------\n| Done! 👌 |\n------------$(DEF_COLOR)"


clean:
	rm -rf $(OBJS_DIR)
	rm -rf $(OBJS_BONUS_DIR)
	make fclean -sC $(LIBFT_DIR)
	make fclean -sC $(PRINTF_DIR)

fclean: clean
	rm -rf $(NAME) $(NAME_BONUS)
	@echo "$(GREEN)$(NAME) and $(NAME_BONUS)$(YELLOW) cleaned$(DEF_COLOR)"

re: fclean all

.PHONY: all clean fclean re
.SILENT: all clean fclean