# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/01 12:47:52 by framos-p          #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2023/06/07 12:13:08 by mpuig-ma         ###   ########.fr        #
=======
#    Updated: 2023/06/07 15:48:10 by mpuig-ma         ###   ########.fr        #
>>>>>>> makefile-readline
#                                                                              #
# **************************************************************************** #

AUTHOR			?=	framos-p, mpuig-ma

MAKE			:=	make --no-print-directory
NAME			:=	minishell
BUILD_DIR		:=	build
SRC_DIR			:=	src
LIBFT_DIR		:=	$(SRC_DIR)/libft
LIBFT			:=	$(LIBFT_DIR)/libft.a

CC				:=	gcc
CFLAGS			:=	-Wall -Wextra -Werror -MMD
#CFLAGS			+=	-g -fsanitize='address,undefined'# uncomment for debugging
LDFLAGS			:=	-L $(SRC_DIR)/libft 
LDLIBS			=	-lft $(LREADLINE)
LREADLINE		:=	-lreadline
INC				:=	-I $(SRC_DIR) -I $(SRC_DIR)/builtins -I $(SRC_DIR)/libft/src
RM				:=	-rm -rf

# Use pkg-config --libs to find where readline library is.

ifneq (, $(shell pkg-config --libs readline))
	LREADLINE	=	$(shell pkg-config --libs readline)
else
	LREADLINE	=	-lreadline
endif

SRC_FILES		:=	$(SRC_DIR)/main.c \
					$(SRC_DIR)/command_do.c \
					$(SRC_DIR)/shell_expand.c \
					$(SRC_DIR)/shell_do.c \
					$(SRC_DIR)/builtins/echo.c \
					$(SRC_DIR)/builtins/pwd.c \
					$(SRC_DIR)/builtins/env.c

OBJ_FILES		=	$(SRC_FILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEP_FILES		=	$(OBJ_FILES:.o=.d)

# Colors

NOSTYLE			:=	\033[0m
GREEN			:=	\033[0;32m
BOLD_CYAN		:=	\033[1;36m

# Function to standarize printing stuff.

define message =
@printf "$(BOLD_CYAN)%-20s: $(GREEN)%s$(NOSTYLE)\n" "$(1)" "$(2)"
endef

.PHONY: all clean fclean re tests check_libs

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ_FILES) $(DEP_FILES) $(SRC_DIR)/$(NAME).h
	@$(CC) $(INC) $(CFLAGS) $(LDFLAGS) $(LDLIBS) $(OBJ_FILES) -o $(basename $@)
	$(call message,"compiled",$(basename $@))

bonus: $(LIBFT) $(BOJB_FILES) $(BDEP_FILES) $(SRC_DIR)/$(NAME).h
	@$(CC) $(INC) $(CFLAGS) $(LDFLAGS) $(LDLIBS) $(BOBJ_FILES) -o $(basename $@)
	$(call message,"compiled",$(basename $@))

tests:
	@make -C tests

check_libs:
	@echo $(LREADLINE)
	@echo $(LDLIBS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(call message,"compiling",$<)
	@$(CC) $(INC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C $(dir $@)

clean:
	@$(RM) $(BUILD_DIR)
	@$(MAKE) fclean -sC $(LIBFT_DIR)
	$(call message,"Files",$(basename $@))
	$(call message,Directory $(BUILD_DIR),$(basename $@))

fclean: clean
	@$(RM) $(NAME)
	@$(RM) bonus
	$(call message,"Program",$(basename $@))

re: fclean
	@$(MAKE)

-include $(DEPS)
