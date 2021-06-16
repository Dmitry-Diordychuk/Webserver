# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/01 19:43:52 by kdustin           #+#    #+#              #
#    Updated: 2021/06/16 14:41:23 by kdustin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := webserv

CXX := clang++

CXXFLAGS := -Wall -Wextra -Werror
CXXFLAGS += -std=c++98 -pedantic
CXXFLAGS += -glldb -DDEBUG							#Debug

BUILD_DIR := ./build
SRC_DIR := ./source

SRCS := File.cpp HTTPException.cpp HTTPMessage.cpp HTTPRequest.cpp \
	HTTPResponse.cpp Location.cpp main.cpp Method.cpp Path.cpp Config.cpp \
	Server.cpp TCP.cpp URI.cpp Utilities.cpp VirtualServer.cpp HTMLGenerator.cpp \
	Desc.cpp Directory.cpp Task.cpp

OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

INC_DIR := ./include
INC_FLAGS := $(addprefix -I,$(INC_DIR))

CXXFLAGS += $(INC_FLAGS)

$(NAME): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.cpp.o: $(SRC_DIR)/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

all: $(NAME)

clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -f $(NAME)
	rm -f valgrind-out.txt

re: fclean all

valgrind: re
	valgrind --leak-check=full \
			 --show-leak-kinds=all \
			 --track-origins=yes \
			 --verbose \
			 --log-file=valgrind-out.txt \
			 ./$(NAME)

.PHONY: all clean fclean re
