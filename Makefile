
SRCS			= $(addprefix srcs/, main.c ${INIT} ${COMMAND} ${STRUCT} ${TOKEN}\
				  ${ENV} ${EXECUTION} ${BUILTINS} ${EXPANSION} ${ERROR} ${SIGNAL}) 

INIT			= $(addprefix init/, init.c)
COMMAND			= $(addprefix command/, create.c redir.c heredoc.c clear.c parse.c)
TOKEN			= $(addprefix token/, parse.c token.c utils.c check.c quote.c clear.c)
ENV				= $(addprefix env/, clone.c clear.c add_envvar.c get_env.c)
EXECUTION		= $(addprefix execution/, execute.c wait.c redirection.c assignement.c search_exe.c run_exe.c child.c)
BUILTINS		= $(addprefix builtins/, $(addprefix functions/, cd.c echo.c pwd.c env.c exit.c export.c unset.c) run_builtin.c is_builtins.c)
EXPANSION		= $(addprefix expansion/, expand.c trim.c expand_cmdargs.c expand_trim.c expand2.c)
ERROR			= $(addprefix error/, error.c)
SIGNAL			= $(addprefix signal/, signal.c)

HEADERS			= $(addprefix headers/, init.h builtins.h env.h error.h token.h struct.h\
				  command.h execution.h expansion.h signal_handler.h)

OBJS			= ${SRCS:.c=.o}

NAME			= minishell

CC				= cc
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
