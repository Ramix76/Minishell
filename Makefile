# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/01 12:47:52 by framos-p          #+#    #+#              #
#    Updated: 2023/06/01 16:43:32 by mpuig-ma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKE			=	make --no-print-directory
NAME			=	minishell

INC				=	inc/
SRC				=	src/
BUILT			=	src/builtins/

LIBFT			:=	libft.a
LIBFT_DIR		:=	$(SRC)libft

SRCS_FILES		=	$(SRC)main.c $(BUILT)echo.c $(BUILT)pwd.c

CC				:=	gcc
CFLAGS			:=	-g -Wall -Wextra -Werror -MMD
CFLAGS			+=	-I src/ -I src/libft/src -I src/builtins
LDFLAGS			:=	-lreadline -L src/libft -lft
RM				:=	rm -rf

OBJS			=	$(SRCS_FILES:%.c=%.o)
DEPS			=	$(SRCS_FILES:%.c=%.d)

# Colors

NOCOLOR			=	\033[0m
BOLD_PURPLE		=	\033[1;35m
BOLD_CYAN		=	\033[1;36m
RED				=	\033[0;91m
YELLOW			=	\033[1;93m
BLUE			=	\033[0;94m
GREEN			=	\033[0;32m

all: $(NAME)

%.o: %.c
				@echo "$(BOLD_CYAN)compiling: [$(RED)$<$(BOLD_PURPLE)]$(NOCOLOR)"
				@$(CC) -I $(INC) $(CFLAGS) -c $< -o $@

$(NAME):		$(LIBFT) $(OBJS)
				@$(CC) $(OBJS) $(CFLAGS) $(LDFLAGS) -o $(NAME)
				@echo "\n$(RED)Minishell Compiled ✅$(DEF_COLOR)\n"

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

clean:
	@$(MAKE) clean -C $(LIBFT_DIR)
	@$(RM) $(OBJS) $(NAME)
	@$(RM) $(DEPS)
	@echo "\n✅$(YELLOW)Clean: $(RED)Removed Minishell's files \n$(NOCOLOR)"

fclean: clean
	@$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re
