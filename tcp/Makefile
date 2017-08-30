#COMPILER
CC = gcc
#CFlAGS AND LIBS
CFLAGS = -std=c99 -Wall -Werror
LIBS = -lpthread -lm
#SOURCE FILES
SRCS := node.c receiver.c
#HEADER FILES
HDRS = node.h receiver.h
#Rules
OBJS := $(SRCS:.c=.o) $(HDRS)
DEPS := $(OBJS:.o=.d)
TARGET = receiver
all: $(TARGET)
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(LIBS) $^ -o $@
#MISC CMDS:
clean:
	rm -vf *.o $(TARGET)
