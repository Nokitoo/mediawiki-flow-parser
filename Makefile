CC = gcc

NAME = flow_parser

SRCS = $(filter-out %~,$(shell ls src))
OBJS = $(addprefix obj/,$(SRCS:.c=.o))

CFLAGS = -W -Wall -Werror -Wextra
LDFLAGS = -Lgumbo-parser -Wl,-Rgumbo-parser -lgumbo -Llibcurl -Wl,-Rlibcurl -lcurl -lssl

all: $(NAME)

$(NAME): $(OBJS)
	 $(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

obj/%.o: src/%.c
	 @mkdir -p obj
	 $(CC) -o $@ -c $< -Iinclude/ -Igumbo-parser/includes/ -Ilibcurl/includes/ $(CFLAGS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
