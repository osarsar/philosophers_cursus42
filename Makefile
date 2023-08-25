SRCS =	philo.c	\
		philo_utils1.c \
		philo_utils2.c \
		philo_utils3.c \

NAME = libft.a

%.o : %.c libft.h
	@echo "Compiling: $<"
	@cc -Wall -Werror -Wextra -c $< -o $@

$(NAME) :  $(SRCS:.c=.o)
	@ar -r $(NAME) $(SRCS:.c=.o)
	@cc -Wall -Werror -Wextra $(NAME) -o philo 
all : $(NAME)

clean :
	@rm -rf $(SRCS:.c=.o) $(SRCSB:.c=.o)

fclean : clean
	@rm -rf $(NAME)
	@rm	philo

re : fclean all