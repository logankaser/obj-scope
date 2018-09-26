# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: logan  <logan@42.us.org>                   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/13 10:03:24 by logan             #+#    #+#              #
#    Updated: 2018/08/31 09:34:10 by lkaser           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = index.js
LIST = uvector matrix vec vec_op main obj_vertex_data obj_elements

SRC_DIR = src
OBJ_DIR = obj

SRC = $(addsuffix .c, $(addprefix src/, $(LIST)))
OBJ = $(addsuffix .bc, $(addprefix $(OBJ_DIR)/, $(LIST)))
DEP = $(OBJ:%.bc=%.d)
CC = emcc
SUB =

CPPFLAGS = -Wall -Wextra -Werror \
-O3 -s USE_WEBGL2=1 -s ALLOW_MEMORY_GROWTH=1 -s WASM=1 \
 $(INCLUDES)

#LDFLAGS = --llvm-lto 3 -O3 --closure 1 --preload-file assets
LDFLAGS = --preload-file assets

all: $(OBJ_DIR) $(NAME)

$(NAME): $(OBJ)
	@for s in $(SUB);\
	do\
		make -sC $$s;\
	done
	@printf "\e[32;1mLinking.. \e[0m\n"
	@$(CC) $(LDFLAGS) $^ -o $@
	@printf "\e[32;1mCreated:\e[0m %s\n" $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

-include $(DEP)

$(OBJ_DIR)/%.bc: $(SRC_DIR)/%.c
	@printf "\e[34;1mCompiling: \e[0m%s\n" $<
	@$(CC) $(CPPFLAGS) -MMD -c $< -o $@

clean:
	@for s in $(SUB);\
	do\
		make -sC $$s clean;\
	done
	@printf "\e[31;1mCleaning..\e[0m\n"
	@rm -f $(OBJ) $(DEP)

fclean:
	@for s in $(SUB);\
	do\
		make -sC $$s fclean;\
	done
	@printf "\e[31;1mFull Cleaning..\e[0m\n"
	@rm -rf $(OBJ_DIR)
	@rm -f $(NAME).js
	@rm -f $(NAME).wasm
	@rm -f $(NAME).data

re:	fclean all

run: all
	python3 -m http.server 8080

.PHONY: clean fclean all re run
