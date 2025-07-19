# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/11 13:06:22 by anpollan          #+#    #+#              #
#    Updated: 2025/07/09 18:57:05 by anpollan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SERVER		= server
CLIENT		= client
LIBFT		= ./libft/libft.a
SRCS_DIR	= ./srcs/
INCL_DIR	= ./incl/
SERVER_SRCS	= ./srcs/server.c
CLIENT_SRCS = ./srcs/client.c
SHARED_SRCS = ./srcs/minitalk_utils.c
SERVER_OBJS	= $(SERVER_SRCS:%.c=%.o)
CLIENT_OBJS	= $(CLIENT_SRCS:%.c=%.o)
SHARED_OBJS = $(SHARED_SRCS:%.c=%.o)
HEADER		= ./incl/minitalk.h
C_FLAGS		= -Wall -Wextra -Werror -g

all: $(SERVER) $(CLIENT)

$(SERVER): $(SERVER_OBJS) $(SHARED_OBJS) $(LIBFT)
	cc $(C_FLAGS) $(SERVER_OBJS) $(SHARED_OBJS) $(LIBFT) -o $(SERVER)

$(CLIENT): $(CLIENT_OBJS) $(SHARED_OBJS) $(LIBFT)
	cc $(C_FLAGS) $(CLIENT_OBJS) $(SHARED_OBJS) $(LIBFT) -o $(CLIENT)

$(LIBFT):
	$(MAKE) -C libft

%.o: %.c $(HEADER)
	cc $(C_FLAGS) -c $< -o $@

clean: 
	rm -rf $(CLIENT_OBJS) $(SERVER_OBJS) $(SHARED_OBJS)
	$(MAKE) -C libft clean

fclean: clean
	rm -rf $(SERVER) $(CLIENT) compile_commands.json
	$(MAKE) -C libft fclean

re: fclean all

.PHONY: all clean fclean re
