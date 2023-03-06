CLIENT		= client
SERVER		= server
SRCS_CLIENT	= $(shell find "./Client" -name "*.c")
OBJS_CLIENT	= $(SRCS_CLIENT:.c=.o)
SRCS_SERVER	= $(shell find "./Server" -name "*.c")
OBJS_SERVER	= $(SRCS_SERVER:.c=.o)
INCS		= -I.
CFLAGS		= -Wall -Wextra -Werror $(INCS)
RM			= rm -f
CC			= cc

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

all:	$(CLIENT) $(SERVER)

$(CLIENT):	$(OBJS_CLIENT)
	$(CC) $(CFLAGS) -o $(CLIENT) $(OBJS_CLIENT)

$(SERVER):	$(OBJS_SERVER)
	$(CC) $(CFLAGS) -o $(SERVER) $(OBJS_SERVER)

clean:
	$(RM) $(OBJS_SERVER) $(OBJS_CLIENT)

fclean: clean
	$(RM) $(CLIENT) $(SERVER)

re: fclean all

.PHONY: all clean fclean re