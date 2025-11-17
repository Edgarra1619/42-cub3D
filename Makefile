NAME = cub3D
SRCS = main.c vector.c error.c init.c parse.c read.c loop.c input.c render.c render_utils.c
INCDIR = ./include/
SRCDIR = ./src/
OBJDIR = ./obj/
LFTDIR = ./libft/
MLXDIR = ./minilibx/
TESTARGS = ./maps/test.cub

CC = clang
CFLAGS = -Wall -Wextra -gdwarf-4 $(INCFLAGS) -D MINIMAP_SIZE=10
INCFLAGS = -I $(INCDIR) -I $(LFTDIR)/include/ -I $(MLXDIR)
MLXFLAGS = -lXext -lX11

VALGFLAGS = --track-origins=yes --leak-check=full

OBJS = $(patsubst %.c, $(OBJDIR)%.o, $(SRCS))
LFT = $(LFTDIR)/libft.a
MLX = $(MLXDIR)/libmlx.a

.PHONY: all clean fclean re

all: $(NAME)

clean:
	rm -fr $(OBJDIR)

fclean: clean
	rm -f $(NAME)
	make $@ -C $(LFTDIR)
	make clean -C $(MLXDIR)

re: clean all

$(NAME): $(OBJS) $(LFT) $(MLX)
	$(CC) $(CFLAGS) $(MLXFLAGS) -lm -o $@ $^

$(OBJS): $(OBJDIR)%.o: $(SRCDIR)%.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -o $@ -c $<

$(LFT):
	make -C $(LFTDIR)

$(MLX):
	make -C $(MLXDIR)

test: $(NAME)
	./$(NAME) $(TESTARGS)

gprof: $(NAME)
	./$(NAME)
	rm gprof-output -f
	gprof $(NAME) > gprof-output

valgrind: $(NAME)
	valgrind $(VALGFLAGS) ./$(NAME) $(TESTARGS)

gdb: $(NAME)
	gdbtui --args $(NAME) $(TESTARGS)

vgdb: $(NAME)
	valgrind $(VALGFLAGS) --vgdb=full --vgdb-error=0 ./$(NAME) $(TESTARGS)
