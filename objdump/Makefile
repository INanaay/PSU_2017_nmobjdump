CFLAGS += -W -Wall -Wextra -Wfloat-equal -Wshadow -Wpointer-arith -Wcast-align
CFLAGS += -Wstrict-prototypes -Wwrite-strings -Waggregate-return -Wconversion
CLFAGS += -Wunreachable-code -Winit-self -Wreturn-type
CFLAGS += -g3

CFLAGS += -iquote include

NAME = ../my_objdump

SRCS = main.c \
	parse64.c \
	getMachine.c \
	parse32.c

INCLUDES = include

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	gcc -o $(NAME) $(OBJS) $(CFLAGS)

clean :
	$(RM) $(OBJS)

fclean:
	$(RM) $(OBJS)
	$(RM) $(NAME)

re : fclean all

.PHONY: all clean flcean re export test
