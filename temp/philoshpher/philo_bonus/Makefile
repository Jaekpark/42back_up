# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaekpark <jaekpark@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/28 15:11:21 by jaekpark          #+#    #+#              #
#    Updated: 2022/08/04 12:44:42 by jaekpark         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

INCS				=	philo_bonus.h
SRCS				=	philo_bonus.c time.c set.c init.c action.c console.c thread.c utils.c check.c
OBJS				= 	$(patsubst %.c, %.o, $(SRCS_FILE))
SRCS_DIR			=	./srcs/
OBJS_DIR			=	./objs/
INCS_DIR			=	./includes/

SRCS_FILE			=	$(addprefix $(SRCS_DIR), $(SRCS))
OBJS_FILE			= 	$(addprefix $(OBJS_DIR), $(notdir $(OBJS)))
INCS_FILE			= 	$(addprefix $(INCS_DIR), $(INCS))

#	Compile settings
CC					=	gcc
RM					=	rm -rf
CFLAGS				=	-Wall -Wextra -Werror
DFLAGS				= 	-Wall -Wextra -Werror -g -fsanitize=address
HEADER_FLAG			=	-I$(INCS_DIR) -lpthread
NAME				=	philo_bonus
DEBUG				=	philo_bonus_debug

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

.c.o			:
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

norm			:	$(SRCS_FILE) $(INCS_FILE)
					@echo $(CYAN) "`date +%y/%m/%d_%H:%M:%S`:: $(NAME) norm check"$(EOC)
					@norminette $(SRCS_FILE) $(INCS_FILE)
					@make norm -C $(LIBFT_DIR)

leaks			:
	 				@osascript -e 'tell app "Terminal" to do script "while true; do leaks minishell; sleep 2; clear; done"'

clean			:
					@echo $(YELLOW) "`date +%y/%m/%d_%H:%M:%S`:: clean $(NAME)" $(EOC)
					@$(RM) $(OBJS_FILE) 
					@echo $(GREEN) "`date +%y/%m/%d_%H:%M:%S`:: OK" $(EOC)

fclean			:
					@echo $(YELLOW) "`date +%y/%m/%d_%H:%M:%S`:: fclean $(NAME)" $(EOC)
					@$(RM) $(DEBUG) $(NAME) $(OBJS_DIR)
					@echo $(GREEN) "`date +%y/%m/%d_%H:%M:%S`:: OK" $(EOC)

re				:	fclean $(NAME)

.PHONY:			all clean fclean re norm leaks debug
