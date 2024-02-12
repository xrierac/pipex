NAME = pipex

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC_DIR = .
OBJ_DIR = .
LIBFT_DIR = libft/

SRCS := pipex.c utils.c
LIBFT := $(LIBFT_DIR)/libft.a

OBJS := $(SRCS:.c=.o)

$(NAME) : $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(LIBFT) :
	make -C $(LIBFT_DIR)
	cp $(LIBFT) .
	mv libft.a $(NAME)

%.o:%.c
	cc $(CFLAGS) -c $< -o $@ 

all: $(NAME)	

clean:
	make -C $(LIBFT_DIR) clean
	rm -f $(OBJS)

fclean: clean 
	rm -f $(LIBFT)
	rm -f $(NAME)
	

re: fclean all

.PHONY : all clean fclean re libft

