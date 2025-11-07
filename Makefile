NAME = cub3D
SRCS = main.c
INCDIR = ./include/
SRCDIR = ./src/
OBJDIR = ./obj/
LFTDIR = ./libft/
TESTARGS = 

CC = cc
CFLAGS = -Wall -Wextra -Werror -gdwarf-4 $(INCFLAGS)
INCFLAGS = -I $(INCDIR) -I $(LFTDIR)/include/

VALGFLAGS = --track-origins=yes --leak-check=full

OBJS = $(patsubst %.c, $(OBJDIR)%.o, $(SRCS))
LFT = $(LFTDIR)/libft.a

.PHONY: all clean fclean re

all: $(NAME)

clean:
	rm -fr $(OBJDIR)

fclean: clean
	rm -f $(NAME)
	make $@ -C $(LFTDIR)

re: clean all

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJS): $(OBJDIR)%.o: $(SRCDIR)%.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -o $@ -c $<

$(LFT):
	make -C $(LFTDIR)

test: $(NAME)
	./$(NAME) $(TESTARGS)

gprof: $(NAME)
	./$(NAME)
	rm gprof-output -f
	gprof $(NAME) > gprof-output

valgrind: $(NAME)
	valgrind $(VALGFLAGS) ./$(NAME)

gdb: $(NAME)
	gdbtui $(NAME)

vgdb: $(NAME)
	valgrind $(VALGFLAGS) --vgdb=full --vgdb-error=0 ./$(NAME)

