NAME		:= td4
SRCS_DIR	:= src
SRCS		:= $(wildcard $(SRCS_DIR)/*.cpp $(SRCS_DIR)/*/*.cpp)
OBJS		:= $(SRCS:.cpp=.o)
DEPS		:= $(OBJS:.o=.d)

CXX			:= c++
CXXFLAGS	:= -Wall -Wextra -Werror

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

.PHONY: clean fclean re
