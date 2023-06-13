# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/02 17:52:52 by mpuig-ma          #+#    #+#              #
#    Updated: 2023/06/13 12:48:05 by mpuig-ma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BUILD_DIR		:=	build
SRC_DIR			:=	../src
LIBFT_DIR		:=	$(SRC_DIR)/libft
LIBFT			:=	$(LIBFT_DIR)/libft.a

CC				:=	gcc
CFLAGS			:=	-Wall -Wextra -Werror -MMD
CFLAGS			+=	-g -fsanitize='address,undefined'# uncomment for debugging
LDFLAGS			:=	-L $(SRC_DIR)/libft -lft -lreadline -ltermcap
INC				:=	-I $(SRC_DIR) -I $(SRC_DIR)/builtins -I $(SRC_DIR)/libft/src
RM				:=	-rm -rf

NOSTYLE			:=	\033[0m
GREEN			:=	\033[0;32m
BOLD_CYAN		:=	\033[1;36m

SRC_FILES		=	$(wildcard test_*.c)
OBJ_FILES		=	$(SRC_FILES:%.c=$(BUILD_DIR)/%.o)

define message =
@printf "$(BOLD_CYAN)%-20s: $(GREEN)%s$(NOSTYLE)\n" "$(1)" "$(2)"
endef

.PHONY: all tests re

define run_test =
echo $1
endef

all: tests

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo $@
	$(CC) $(INC) $(CFLAGS) -c $< -o $@

tests: $(LIBFT) $(OBJ_FILES)
	@for file in $(SRC_FILES); do \
		gcc $(INC) $(LDFLAGS) test.utils.c $(SRC_DIR)/utils.c $$file -o $$(basename $$file .c); \
		./$$(basename $$file .c); rm $$(basename $$file .c); \
		done

leaks: $(LIBFT) $(OBJ_FILES)
	@for file in $(SRC_FILES); do \
		gcc $(INC) $(LDFLAGS) test.utils.c $$file -o $$(basename $$file .c); \
		leaks --atExit -- ./$$(basename $$file .c); rm $$(basename $$file .c); \
		done

$(LIBFT):
	$(MAKE) -C $(dir $@)

re:
	@make re -C $(SRC_DIR)/libft
	$(MAKE)
