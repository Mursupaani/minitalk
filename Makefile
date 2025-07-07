# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/11 13:06:22 by anpollan          #+#    #+#              #
#    Updated: 2025/07/07 11:56:39 by anpollan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SERVER		= server
CLIENT		= client
LIBFT		= ./libft/libft.a
SERVER_SRCS	= server.c
CLIENT_SRCS = client.c
SERVER_OBJS	= $(SERVER_SRCS:%.c=%.o)
CLIENT_OBJS	= $(CLIENT_SRCS:%.c=%.o)
HEADER		= minitalk.h
C_FLAGS		= -Wall -Wextra -Werror -g

all: $(SERVER) $(CLIENT)

# $(SERVER): $(OBJS) $(LIBFT)
# 	cc $(C_FLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(SERVER): $(SERVER_OBJS)
	cc $(C_FLAGS) $(SERVER_OBJS) -o $(SERVER)

$(CLIENT): $(CLIENT_OBJS)
	cc $(C_FLAGS) $(CLIENT_OBJS) -o $(CLIENT)

$(LIBFT):
	$(MAKE) -C libft

%.o: %.c $(HEADER)
	cc $(C_FLAGS) -c $< -o $@

# clean: 
# 	rm -rf $(OBJS)
# 	$(MAKE) -C libft clean

clean: 
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(SERVER) $(CLIENT) compile_commands.json

re: fclean all

.PHONY: all clean fclean re
