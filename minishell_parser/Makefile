
SRCS			= $(addprefix srcs/, main.c error.c ${COMMAND} ${STRUCT} ${TOKEN} ${ENV} ${PRINT}) 

COMMAND			= $(addprefix command/, command.c)
STRUCT			= $(addprefix struct/, create.c clear.c delete.c)
TOKEN			= $(addprefix token/, token.c check.c)
HEADERS			= $(addprefix headers/, error.h token.h struct.h command.h print.h execution.h)
ENV				= $(addprefix env/, env.c)
EXECUTION		= $(addprefix execution/, exit.c stream.c)

PRINT			= $(addprefix print/, print.c)

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
