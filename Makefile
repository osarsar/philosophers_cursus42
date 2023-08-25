# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: osarsar <osarsar@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/26 00:00:11 by osarsar           #+#    #+#              #
#    Updated: 2023/08/26 00:04:11 by osarsar          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	philo.c	\
		philo_utils1.c \
		philo_utils2.c \
		philo_utils3.c \

NAME = philo.a

%.o : %.c philo.h
	@echo "Compiling: $<"
	@cc -Wall -Werror -Wextra -c $< -o $@

$(NAME) :  $(SRCS:.c=.o)
	@ar -r $(NAME) $(SRCS:.c=.o)
	@cc -Wall -Werror -Wextra $(NAME) -o philo
all : $(NAME)

clean :
	@rm -rf $(SRCS:.c=.o)

fclean : clean
	@rm -rf $(NAME)
	@rm -rf philo
	
re : fclean all