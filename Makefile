NAME		:= td4
SRCS_DIR	:= src
TEST_DIR	:= test
SRCS		:= $(wildcard $(SRCS_DIR)/*.cpp $(SRCS_DIR)/*/*.cpp)
OBJS		:= $(SRCS:.cpp=.o)
DEPS		:= $(OBJS:.o=.d)

CXX			:= c++
CXXFLAGS	:= -MMD -MP #-Wall -Wextra -Werror

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

test:
	$(CXX) $(CXXFLAGS) -D TEST $(SRCS_DIR)/TD4.cpp $(TEST_DIR)/TD4_test.cpp -o td4_test && ./td4_test

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(DEPS)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

-include $(DEPS) $(TEST_DEPS)

.PHONY: test clean fclean re
