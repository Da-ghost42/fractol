NAME = fractol

SRC = fractol.c fractol_tools.c mandelbrot.c hooks.c julia.c burnningship.c

LIB = lib/libft.a

HEADER = fractol.h

HEAD = define.h

OBJ = fractol.o fractol_tools.o mandelbrot.o hooks.o julia.o burnningship.o

RM = rm -rf

CFLAGS = -Wall -Wextra -Werror

all : ${NAME}

${NAME} : ${OBJ} 
	@echo "compiling..."
	@make -C lib
	@${CC} ${OBJ} ${LIB} -lmlx -lmlx -framework  OpenGL -framework AppKit -o ${NAME}

%.o: %.c $(HEADER) $(HEAD)
	@$(CC) $(CFLAGS) -Imlx -c $< -o $@ 

clean :
	@${RM} ${OBJ} ${NAME}
fclean : clean
	@make fclean -C lib
	@${RM} ${NAME}
re : fclean all

.PHONY : all re clean fclean

.SILENT : re fclean clean all