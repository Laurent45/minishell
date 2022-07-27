
SRCS			= $(addprefix srcs/, main.c ${COMMAND} ${STRUCT} ${TOKEN}\
				  ${ENV} ${PRINT} ${EXECUTION} ${BUILTINS} ${EXPANSION} ${ERROR}) 

COMMAND			= $(addprefix command/, create.c redirection.c clear.c parse.c)
STRUCT			= $(addprefix struct/, delete.c)
TOKEN			= $(addprefix token/, parse.c create.c clear.c check.c)
HEADERS			= $(addprefix headers/, error.h token.h struct.h command.h print.h execution.h)
ENV				= $(addprefix env/, create.c clear.c env.c)
EXECUTION		= $(addprefix execution/, execute.c stream.c exit.c child.c failed.c simple_cmd/execute.c utils.c)
BUILTINS		= $(addprefix builtins/, init.c cd.c echo.c env.c exit.c export.c pwd.c unset.c)
EXPANSION		= $(addprefix expansion/, expand.c trim.c expand_cmdargs.c)
ERROR			= $(addprefix error/, error.c)

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
	${CC} ${CFLAGS} ${OBJS} -L${P_LIBFT} -lft -lreadline -o ${NAME}

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
