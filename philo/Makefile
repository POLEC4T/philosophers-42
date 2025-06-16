NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -g3
SRC_FILES = main.c philos_threads.c utils.c ft_atoi.c inits.c \
			main_thread.c free.c prints.c time.c
RM = rm -f
OBJ_DIR = .objs
SRC_DIR = src
SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))
INCLUDE_DIR = ./include
INCLUDES = -I$(INCLUDE_DIR)
HEADER = $(addprefix $(INCLUDE_DIR)/, philos.h)

all: $(NAME)
	@echo "$(NAME) ready to run!"

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $@ $^
	@echo "Created $(NAME)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER) Makefile | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)
	@echo "Compiled $< to $@"

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	$(RM)r $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re