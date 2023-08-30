# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: osarsar <osarsar@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/26 00:00:11 by osarsar           #+#    #+#              #
#    Updated: 2023/08/29 21:25:48 by osarsar          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	philo.c	\
		philo_utils1.c \
		philo_utils2.c \
		philo_utils3.c \

NAME = philo.a

FLAGS = -Wall -Werror -Wextra

%.o : %.c philo.h
	@echo "Compiling: $<"
	@cc $(FLAGS) -c $< -o $@

$(NAME) :  $(SRCS:.c=.o)
	@ar -r $(NAME) $(SRCS:.c=.o)
	@cc $(FLAGS) $(NAME) -o philo
all : $(NAME)

clean :
	@rm -rf $(SRCS:.c=.o)

fclean : clean
	@rm -rf $(NAME)
	@rm -rf philo
	
re : fclean all