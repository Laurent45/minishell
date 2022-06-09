
SRCS			= $(addprefix srcs/, main.c error.c token/token.c\
				  token/clear_token.c command/command.c)

HEADERS			= $(addprefix headers/, error.h token.h struct.h command.h)

OBJS			= ${SRCS:.c=.o}

NAME			= parser

CC				= gcc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror -g

P_HEADERS		= headers/
P_LIBFT			= libft/
P_LIBFT_H		= libft/headers/

%.o: %.c ${HEADERS} 
		${CC} ${CFLAGS}\
		-I${P_HEADERS} -I${P_LIBFT_H}\
		-c $< -o ${<:.c=.o}

all: libft_make ${NAME}

${NAME}: ${OBJS} 
	${CC} ${CFLAGS} ${OBJS} -L${P_LIBFT} -lft -o ${NAME}

libft_make:
	@make -C libft/
libft_clean:
	@make fclean -C libft/
	
clean:
		${RM} ${OBJS} 

fclean:	clean libft_clean
		${RM} ${NAME} 

re:		fclean all

.PHONY: all clean fclean re
