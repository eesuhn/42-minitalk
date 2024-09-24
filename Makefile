TARGETS := server client

SRCS := \
		server \
		client \

SRCS := $(SRCS:=.c)

OBJS := $(SRCS:.c=.o)

CFLAGS := -Wall -Wextra -Werror

LDFLAGS := -Llibft -lft

LIBFT := ./libft/libft.a

all: $(TARGETS)

$(TARGETS): %: %.o $(LIBFT)
	cc $(CFLAGS) -o $@ $< $(LDFLAGS)

$(LIBFT):
	@$(MAKE) -C ./libft > /dev/null

%.o: %.c
	cc $(CFLAGS) -c $< -o $@

clean:
	@$(MAKE) clean -C ./libft > /dev/null
	rm -f $(OBJS)

fclean: clean
	@$(MAKE) fclean -C ./libft > /dev/null
	rm -f $(TARGETS)

re: fclean all

.PHONY: all clean fclean re $(TARGETS)
