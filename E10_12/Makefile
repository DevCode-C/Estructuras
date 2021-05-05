TARGET = E10_12
CC = gcc
OBJS = main.o 
HEADERS = -I .
CFLAGS = -c -std=c99 -Wall -g -O0 -o
LDFLAGS += -lm 

all:$(OBJS) $(TARGET)

$(TARGET) : $(OBJS)
	@$(CC) $(OBJS) $(LDFLAGS) -o $(TARGET) 

%.o : %.c  
	@$(CC) $(CFLAGS) $@ $^

.PHONY : clean
clean : 
	@rm -f *.o $(TARGET)
.PHONY : do
do : 
	@./$(TARGET)
.PHONY : debug
debug :
	@gdb $(TARGET)
