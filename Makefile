NAME = fractol

SRC = fractol.c fractol_tools.c

LIB = lib/libft.a

HEADER = fractol.h

OBJ = fractol.o fractol_tools.o

RM = rm -rf

CFLAGS = -Wall -Wextra -Werror -g
all : ${NAME}

${NAME} : ${OBJ}
	@make -C lib
	@${CC} ${OBJ} ${LIB} -lmlx -lmlx -framework  OpenGL -framework AppKit -o ${NAME}

%.o: %.c HEADER
	@$(CC) $(CFLAGS) -Imlx -c $^ -o $@ 

clean :
	@${RM} ${OBJ} ${NAME}
fclean : clean
	@make fclean -C lib
	@${RM} ${NAME}
re : fclean all

.PHONY : all re clean fclean
