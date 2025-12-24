# Variables

CC= cc
CFLAGS= -Wall -Wextra -Werror -Wpedantic -Iincludes -pthread

SRC= \
	main.c \
	action.c \
	notify.c \
	memory.c \
	philosophers.c \
	errors.c \
	utils.c \
	time.c \
	struct.c \
	check.c 

OBJ= $(SRC:.c=.o)
NAME= philo

# Makeflags
MAKEFLAGS += --no-print-directory

# Colors
RED := \033[31m
GREEN := \033[32m
YELLOW := \033[33m
BLUE := \033[34m
RESET := \033[0m

# Rules
all: $(NAME)

$(NAME): $(OBJ)
	@echo "💻 ${GREEN}Building:${RESET} ${NAME}"
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	@echo "🛠️  ${BLUE}Compiling:${RESET} $< to $@"
	@$(CC) $(CFLAGS) -c $< -o $@

debug: CFLAGS += -g3 -o0 -fsanitize=thread
debug: re
	@echo "⚠️  ${RED}Compilation mode:${RESET} debug"

clean:
	@echo "🧹 ${YELLOW}Cleaning: ${RESET}project objects"
	@rm -rf $(OBJ)

fclean: clean
	@echo "💣 ${YELLOW}Cleaning: ${RESET}everything"
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus debug
