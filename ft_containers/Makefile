INCS				=	algorithm/equal.hpp algorithm/lexicographical_compare.hpp container/map.hpp container/stack.hpp container/vector.hpp \
						iterator/advance.hpp iterator/bst_const_iterator.hpp iterator/bst_iterator.hpp iterator/distance.hpp iterator/iterator_traits.hpp \
						iterator/iterator.hpp iterator/reverse_iterator.hpp \
						type_traits/enable_if.hpp type_traits/is_integral.hpp type_traits/remove_const.hpp utility/binary_search_tree.hpp utility/bst_node.hpp \
						utility/make_pair.hpp utility/nullptr_t utility/pair.hpp utility/utility.hpp

SRCS				=	main.cpp
OBJS				= 	$(patsubst %.cpp, %.o, $(SRCS_FILE))
SRCS_DIR			=	./
OBJS_DIR			=	./
INCS_DIR			=	./

SRCS_FILE			=	$(addprefix $(SRCS_DIR), $(SRCS))
OBJS_FILE			= 	$(addprefix $(OBJS_DIR), $(notdir $(OBJS)))
INCS_FILE			= 	$(addprefix $(INCS_DIR), $(INCS))

#	Compile settings
CC					=	c++
RM					=	rm -rf
CFLAGS				=	-Wall -Wextra -Werror -g -std=c++98
DFLAGS				= 	-Wall -Wextra -Werror -g -std=c++98 -fsanitize=address
HEADER_FLAG			=	-I$(INCS_DIR)
NAME				=	a.out
DEBUG				=	debug.out

#	Color settings
BLACK			=	"\033[1;30m"
RED				=	"\033[1;31m"
GREEN			=	"\033[1;32m"
YELLOW			=	"\033[1;33m"
BLUE			=	"\033[1;34m"
CYAN			=	"\033[1;35m"
PURPLE			=	"\033[1;36m"
WHITE			=	"\033[1;37m"
EOC				=	"\033[0;0m"

.cpp.o			:
					@clear
					@echo $(BLUE)
					$(CC) $(CFLAGS) -c $< -o $(addprefix $(OBJS_DIR), $(notdir $@))
					@echo $(EOC)

all				:	$(NAME)

debug			:	$(DEBUG)


$(NAME)			:	$(OBJS_DIR) $(OBJS)
					@clear
					@echo $(GREEN)
					$(CC) $(CFLAGS) $(HEADER_FLAG) $(OBJS_FILE) -o $@
					@echo $(EOC)
					@echo $(YELLOW) "`date +%y/%m/%d_%H:%M:%S`:: Compiling $@"
					@echo $(GREEN) "`date +%y/%m/%d_%H:%M:%S`:: OK" $(EOC)

$(DEBUG)		:	$(OBJS_DIR) $(OBJS)
					@clear
					@echo $(PURPLE)
					$(CC) $(DFLAGS) $(HEADER_FLAG) $(OBJS_FILE) -o $@
					@echo $(EOC)
					@echo $(YELLOW) "`date +%y/%m/%d_%H:%M:%S`:: Compiling $@"
					@echo $(GREEN) "`date +%y/%m/%d_%H:%M:%S`:: OK" $(EOC)

$(OBJS_DIR)		:
					@mkdir -p $(OBJS_DIR)

leaks			:
	 				@osascript -e 'tell app "Terminal" to do script "while true; do leaks $(NAME); sleep 2; clear; done"'

clean			:
					@echo $(YELLOW) "`date +%y/%m/%d_%H:%M:%S`:: clean $(NAME)" $(EOC)
					@$(RM) $(OBJS_FILE) 
					@echo $(GREEN) "`date +%y/%m/%d_%H:%M:%S`:: OK" $(EOC)

fclean			:
					@echo $(YELLOW) "`date +%y/%m/%d_%H:%M:%S`:: fclean $(NAME)" $(EOC)
					@$(RM) $(DEBUG) $(NAME) $(OBJS_FILE)
					@echo $(GREEN) "`date +%y/%m/%d_%H:%M:%S`:: OK" $(EOC)

re				:	fclean $(NAME)

.PHONY:			all clean fclean re leaks debug
