NAME = fractol

SRC = fractol.c

LIB = lib/libft.a

HEADER = fractol.h

OBJ = fractol.o

RM = rm -rf

all : ${NAME}

${NAME} : ${OBJ}
	@make -C lib
	@${CC} ${OBJ} ${LIB} -lmlx -lmlx -framework  OpenGL -framework AppKit -o ${NAME}

%.o: %.c HEADER
	@$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@

clean :
	@${RM} ${OBJ} ${NAME}
fclean : clean
	@make fclean -C lib
	@${RM} ${NAME}
re : fclean all

.PHONY : all re clean fclean
