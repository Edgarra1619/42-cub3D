NAME = cub3D
SRCS =  main.c vector.c vector_float.c error.c init.c parse.c parse_prop.c
SRCS += parse_map.c read.c validate.c loop.c input.c collision.c player.c
SRCS += entity.c render.c render_utils.c render_sprites.c minimap.c raycast.c
SRCS += sort_sprites.c
INCDIR = ./include/
SRCDIR = ./src/
OBJDIR = ./obj/
LFTDIR = ./libft/
MLXDIR = ./minilibx/
TESTARGS = scenes/example.cub

CC = cc
CFLAGS = -Wall -Wextra -Werror -O3 $(INCFLAGS)
INCFLAGS = -I $(INCDIR) -I $(LFTDIR)/include/ -I $(MLXDIR)
MLXFLAGS = -lXext -lX11 -lXfixes

VALGFLAGS = --leak-check=full --show-leak-kinds=all

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
	./$(NAME) $(TESTARGS)
	rm gprof-output -f
	gprof $(NAME) > gprof-output

valgrind: $(NAME)
	valgrind $(VALGFLAGS) ./$(NAME) $(TESTARGS)

gdb: $(NAME)
	gdbtui --args $(NAME) $(TESTARGS)

vgdb: $(NAME)
	valgrind $(VALGFLAGS) --vgdb=full --vgdb-error=0 ./$(NAME) $(TESTARGS)
