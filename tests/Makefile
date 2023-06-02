# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpuig-ma <mpuig-ma@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/02 17:52:52 by mpuig-ma          #+#    #+#              #
#    Updated: 2023/06/02 17:59:16 by mpuig-ma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BUILD_DIR		:=	build
SRC_DIR			:=	../src
LIBFT_DIR		:=	$(SRC_DIR)/libft
LIBFT			:=	$(LIBFT_DIR)/libft.a

CC				:=	gcc
CFLAGS			:=	-Wall -Wextra -Werror -MMD
CFLAGS			+=	-g -fsanitize='address,undefined'# uncomment for debugging
LDFLAGS			:=	-L $(SRC_DIR)/libft -lft -lreadline
INC				:=	-I $(SRC_DIR) -I $(SRC_DIR)/builtins -I $(SRC_DIR)/libft/src
RM				:=	-rm -rf

NOSTYLE			:=	\033[0m
GREEN			:=	\033[0;32m
BOLD_CYAN		:=	\033[1;36m

SRC_FILES		:=	test_*.c
OBJ_FILES		=	$(SRC_FILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEP_FILES		=	$(OBJ_FILES:.o=.d)

define message =
@printf "$(BOLD_CYAN)%-20s: $(GREEN)%s$(NOSTYLE)\n" "$(1)" "$(2)"
endef

.PHONY: all tests

all: $(LIBFT) tests

tests: $(LIBFT) $(OBJ_FILES) $(DEP_FILES) #header?
	$(CC) $(INC) $(CFLAGS) $(LDFLAGS) $(OBJ_FILES) -o $(basename $@)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(INC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(dir $@)
