NAME = fractol

SRC = fractil.c

OBJ = fractol.o

RM = rm -rf

all : ${NAME}

${NAME} : ${OBJ}
	${CC} ${OBJ} -lmlx -lmlx -framework OpenGL -framework AppKit -o ${NAME}

%.o: %.c
	$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@

clean :
	${RM} ${OBJ} ${NAME}