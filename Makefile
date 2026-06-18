NAME		= libgnl.a
BONUS_NAME	= libgnl_bonus.a

CC		= cc
CFLAGS		= -Wall -Wextra -Werror
AR		= ar rcs
RM		= rm -f

SRCS		= get_next_line.c get_next_line_utils.c
OBJS		= $(SRCS:.c=.o)
BONUS_SRCS	= get_next_line_bonus.c get_next_line_utils_bonus.c
BONUS_OBJS	= $(BONUS_SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(BONUS_OBJS)
	$(AR) $(BONUS_NAME) $(BONUS_OBJS)

test:
	$(CC) $(CFLAGS) -D BUFFER_SIZE=42 -c $(SRCS)
	$(CC) $(CFLAGS) -D BUFFER_SIZE=42 -c $(BONUS_SRCS)

norm:
	norminette get_next_line.c get_next_line_utils.c get_next_line.h
	norminette get_next_line_bonus.c get_next_line_utils_bonus.c \
		get_next_line_bonus.h

clean:
	$(RM) $(OBJS) $(BONUS_OBJS)

fclean: clean
	$(RM) $(NAME) $(BONUS_NAME)

re: fclean all

.PHONY: all bonus test norm clean fclean re
