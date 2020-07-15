CC=gcc
CFLAGS=-Wall -std=c99

TARGET=sunrise
SRCS = sunrise.c
INC = -I./
OBJS = $(SRCS:.c=.o)

$(TARGET):$(OBJS)
	$(CC) -o $@ $^
.PHONY:clean
clean:
	rm -rf $(TARGET) $(OBJS)
	
%.o:%.c
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<
