CC = gcc

NAME = flow_parser

SRCS = $(filter-out %~,$(shell ls src))
OBJS = $(addprefix obj/,$(SRCS:.c=.o))

CFLAGS = -W -Wall -Werror -Wextra

LDFLAGS = -Lgumbo-parser -Wl,-Rgumbo-parser -Ljansson -Wl,-Rjansson -lgumbo -ljansson -Llibcurl -Wl,-Rlibcurl -lcurl -lssl

all: $(NAME)

$(NAME): $(OBJS)
	 $(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

obj/%.o: src/%.c
	 @mkdir -p obj
	 $(CC) -o $@ -c $< -I include/ -Igumbo-parser/includes/ -Ijansson/include/ -Ilibcurl/includes/ $(CFLAGS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
