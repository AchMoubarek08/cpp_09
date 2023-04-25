CC = c++ -Wall -Wextra -Werror -std=c++98 -g -o RPN
SRC = main.cpp

NAME = RPN

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(SRC)

clean:
	rm -f $(NAME)

fclean: clean	
	rm -f $(NAME) 

re : fclean all
		@rm -r *.dSYM