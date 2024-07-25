# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gdero <gdero@student.s19.be>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/06 16:07:27 by gdero             #+#    #+#              #
#    Updated: 2024/07/23 19:42:06 by gdero            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = philo.c \
		fill_struct.c \
		thread_function.c \
		monitoring.c \
		time_gestion.c

OBJECTS = $(SRCS:.c=.o)

HEADER = philo.h
NAME = philo
CFLAGS = -g -Wall -Wextra -Werror -pthread
SANITIZING = -fsanitize=thread
CC = gcc -pthread
RM = rm -f

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) ${OBJECTS} -I ${HEADER} -o ${NAME} ${SANITIZING}

.c.o:
	$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}
	
all: $(NAME)

clean:
	$(RM) $(OBJECTS) $(OBJBONUS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
