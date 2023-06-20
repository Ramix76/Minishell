# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/01 12:47:52 by framos-p          #+#    #+#              #
#    Updated: 2023/06/20 11:44:04 by mpuig-ma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

AUTHOR			?=	framos-p, mpuig-ma
BUILD_DIR		:=	build
CC				:=	gcc
CFLAGS			:=	-Wall -Wextra -Werror -MMD
#CFLAGS			+=	-g -fsanitize='address,undefined'# uncomment for debugging
INC				=	-I $(SRC_DIR) -I $(SRC_DIR)/builtins -I $(SRC_DIR)/libft/src
INC				+=	$(shell pkg-config --cflags readline)
LDFLAGS			=	-L $(SRC_DIR)/libft 
LDLIBS			=	-lft $(LREADLINE)
LREADLINE		:=	-lreadline
LIBFT			=	$(LIBFT_DIR)/libft.a
LIBFT_DIR		=	$(SRC_DIR)/libft
MAKE			:=	make --no-print-directory
NAME			:=	minishell
RM				:=	-rm -rf
SHELL			:=	/bin/sh
SRC_DIR			:=	src

# Use pkg-config --libs to find where readline library is.

LREADLINE		:=	$(shell 2>/dev/null pkg-config --libs readline)

ifeq (,$(LREADLINE))
	LREADLINE	:=	-lreadline
endif

#/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk

SRC_FILES		:=	$(SRC_DIR)/main.c \
					$(SRC_DIR)/command_do.c \
					$(SRC_DIR)/job_control.c \
					$(SRC_DIR)/pipe_do.c \
					$(SRC_DIR)/shell_do.c \
					$(SRC_DIR)/shell_expand.c \
					$(SRC_DIR)/utils.c \
					$(SRC_DIR)/builtins/builtin_do.c \
					$(SRC_DIR)/builtins/echo.c \
					$(SRC_DIR)/builtins/pwd.c \
					$(SRC_DIR)/builtins/env.c \
					$(SRC_DIR)/builtins/cd.c

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
	@echo $(CFLAGS)
	@echo $(LDLIBS)
	@echo $(INC)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(call message,"compiling",$<)
	@$(CC) $(INC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C $(dir $@)

clean:
	@$(RM) $(BUILD_DIR)
	@$(MAKE) fclean -sC $(LIBFT_DIR)
	$(call message,$(BUILD_DIR),$(basename $@))

fclean: clean
	@$(RM) $(NAME)
	@$(RM) bonus
	$(call message,$(NAME),$(basename $@))

re: fclean
	@$(MAKE)

-include $(DEPS)
