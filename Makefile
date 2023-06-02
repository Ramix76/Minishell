# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/01 12:47:52 by framos-p          #+#    #+#              #
#    Updated: 2023/06/02 17:52:16 by mpuig-ma         ###   ########.fr        #
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
RM				:=	-rm -rf

SRC_FILES		:=	$(SRC_DIR)/main.c $(SRC_DIR)/builtins/echo.c $(SRC_DIR)/builtins/pwd.c
OBJ_FILES		=	$(SRC_FILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEP_FILES		=	$(OBJ_FILES:.o=.d)

# Colors

NOSTYLE			=	\033[0m
GREEN			=	\033[0;32m
BOLD_CYAN		=	\033[1;36m

define message =
@printf "$(BOLD_CYAN)%-20s: $(GREEN)%s$(NOSTYLE)\n" "$(1)" "$(2)"
endef

.PHONY: all clean fclean re tests

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ_FILES) $(DEP_FILES) #header?
	@$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ_FILES) -o $(basename $@)
	$(call message,"compiled",$(basename $@))

bonus: $(LIBFT) $(BOJB_FILES) $(BDEP_FILES) #header?
	@$(CC) $(INC) $(CFLAGS) $(LDFLAGS) $(BOBJ_FILES) -o $(basename $@)
	$(call message,"compiled",$(basename $@))

tests:
	@make -C tests

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
