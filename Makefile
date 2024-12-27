TARGETS = server client

MAKE = make --no-print-directory

SRCS = \
		server \
		client \

SRCS := $(SRCS:=.c)

OBJS := $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror

LDFLAGS = -Llibft -lft

LIBFT = ./libft/libft.a

all: $(TARGETS)

$(TARGETS): %: %.o $(LIBFT) $(OBJS)
	cc $(CFLAGS) -o $@ $< $(LDFLAGS)

$(LIBFT):
	@echo "Compiling libft..."
	@$(MAKE) -C ./libft

%.o: %.c
	@cc $(CFLAGS) -c $< -o $@

clean:
	@echo "\033[0;33mCleaning...\033[0m"
	@$(MAKE) clean -C ./libft
	@rm -f $(OBJS)

fclean: clean
	@$(MAKE) fclean -C ./libft
	@rm -f $(TARGETS)

re: fclean all

.PHONY: all clean fclean re $(TARGETS)
