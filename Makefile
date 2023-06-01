# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/01 12:47:52 by framos-p          #+#    #+#              #
#    Updated: 2023/06/01 12:52:12 by framos-p         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKE			=	make --no-print-directory
NAME			=	minishell

INC				=	inc/
SRC				=	src/
BUILT			=	src/builtins/

SRCS_FILES		=	$(SRC)main.c $(BUILT)echo.c $(BUILT)pwd.c

CC				=	gcc
FLAGS			=	-g -Wall -Wextra -Werror -MMD -lreadline
RM				=	rm -rf

OBJS			=	$(SRCS_FILES:%.c=%.o)

DEPS			=	$(SRCS_FILES:%.c=%.d)

# Colors

NOCOLOR			=	\033[0m
BOLD_PURPLE		=	\033[1;35m
BOLD_CYAN		=	\033[1;36m
RED				=	\033[0;91m
YELLOW			=	\033[5;93m
BLUE			=	\033[0;94m
GREEN			=	\033[0;32m

all:
				@$(MAKE) $(NAME)

%.o: %.c
				@echo "$(BOLD_CYAN)compiling: [$(RED)$<$(BOLD_PURPLE)]"
				@$(CC) $(FLAGS) -I $(INC) -c $< -o $@

$(NAME)::		$(OBJS) Makefile
				@$(CC) $(FLAGS) $(OBJS) -o $(NAME)

$(NAME)::
				@echo "\n$(RED)Minishell Compiled ✅$(DEF_COLOR)\n"

clean:
				@$(RM) $(OBJS) $(NAME)
				@$(RM) $(DEPS)
				@echo "\n✅$(YELLOW)Clean: $(RED)Removed Minishell's files \n$(DEF_COLOR)"

fclean: clean

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re
