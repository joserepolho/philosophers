CC = cc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=thread
RM = rm -f

PTHEAD_FLAG = -pthread

NAME = philo

SRCS_FILE =	philo.c	\
			utils.c	\
			exec_set.c	\
			exec_start.c	\
			exec_support.c	\
			philo_status.c	\

SRCS = $(addprefix $(SRCS_DIR), $(SRCS_FILE))
OBJS = $(SRCS:%.c=%.o)

$(NAME) :	$(OBJS)
			$(CC) $(CFLAGS) $(PTHEAD_FLAG) -o $(NAME) $(OBJS)

all		:	$(NAME)

clean	:	
			$(RM) $(OBJS)

fclean	:	clean
			$(RM) $(NAME)

re		:	fclean all

.PHONY	:	all clean fclean re