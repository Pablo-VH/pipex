# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pavicent <pavicent@student.42madrid>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/04 12:03:48 by pavicent          #+#    #+#              #
#    Updated: 2024/05/16 09:31:01 by pavicent         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libftprintf.a
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -I $(INC)
RM		= rm -rf
AR		= ar rcs
LIB		= ranlib
INC		= inc/

SRCS_FILES		=	ft_printf.c\
		  			ft_putchar.c\
		  			ft_putstr.c\
		  			ft_putnbr.c\
		  			ft_putunbr.c\
		  			ft_putnbr_base.c\
		  			ft_strlen.c\

SRCS_DIR			= srcs/
OBJS_DIR			= objs/
SRCS				= $(addprefix $(SRCS_DIR), $(SRCS_FILES))
OBJS				= $(addprefix $(OBJS_DIR), $(OBJS_FILES))
OBJS_FILES			= $(SRCS_FILES:%.c=%.o)

#colors
BOLD_PURPLE	= \033[1;35m
BOLD_CYAN	= \033[1;36m
BOLD_YELLOW	= \033[1;33m
NO_COLOR	= \033[0m
DEF_COLOR 	= \033[0;39m
GRAY 		= \033[0;90m
RED 		= \033[0;91m
GREEN		= \033[0;92m
YELLOW 		= \033[0;93m
BLUE 		= \033[0;94m
MAGENTA 	= \033[0;95m
CYAN 		= \033[0;96m
WHITE		= \033[0;97m

all: $(NAME)

$(NAME): $(OBJS)
	@$(AR) $(NAME) $(OBJS)
	@$(LIB) $(NAME)
	@echo "$(GREEN)\nft_printf.a compiled!$(DEF_COLOR)"

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@[ -d $(OBJS_DIR) ] | mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJS_DIR)
	@echo "$(GREEN)\nft_printf$(YELLOW) cleaned$(DEF_COLOR)"

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.SILENT: all $(NAME) $(OBJS) re clean fclean
.PHONY: all clean fclean re
