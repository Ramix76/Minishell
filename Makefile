# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/01 12:47:52 by framos-p          #+#    #+#              #
#    Updated: 2023/06/01 18:11:01 by mpuig-ma         ###   ########.fr        #
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
CFLAGS			+=	-g -fsanitize='address,undefined'# uncomment for debugging
LDFLAGS			:=	-L src/libft -lft -lreadline
INC				:=	-I src -I src/builtins -I src/libft/src
RM				:=	rm -rf

SRC_FILES		:=	$(SRC_DIR)/main.c $(SRC_DIR)/builtins/echo.c $(SRC_DIR)/builtins/pwd.c
OBJ_FILES		=	$(SRC_FILES:%.c=$(BUILD_DIR)/%.o)
DEP_FILES		=	$(SRC_FILES:%.c=$(BUILD_DIR)/%.d)

# Colors

NOSTYLE			=	\033[0m
GREEN			=	\033[0;32m
BOLD_CYAN		=	\033[1;36m

define message =
@printf "$(BOLD_CYAN)%-10s: $(GREEN)%s$(NOSTYLE)\n" "$(1)" "$(2)"
endef

.PHONY: all clean fclean re

all: $(NAME)

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(call message,"compiling",$<)
	@$(CC) $(INC) $(CFLAGS) -c $< -o $@

$(NAME): $(LIBFT) $(OBJ_FILES) $(DEP_FILES) #header?
	@$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ_FILES) -o $(basename $@)
	$(call message,"compiled",$(basename $@))

bonus: $(LIBFT) $(BOJB_FILES) $(BDEP_FILES) #header?
	@$(CC) $(INC) $(CFLAGS) $(LDFLAGS) $(BOBJ_FILES) -o $(basename $@)
	$(call message,"compiled",$(basename $@))

$(LIBFT):
	@$(MAKE) -C $(dir $@)

clean:
	@$(RM) $(BUILD_DIR)
	@$(MAKE) fclean -C $(LIBFT_DIR)

fclean: clean
	$(RM) $(NAME)
	$(RM) bonus

re: fclean
	@$(MAKE)

-include $(DEPS)
