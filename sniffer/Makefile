CC = gcc
TARGET = sniffer
SOURCE = sniffer.c
OBJS = sniffer.o
HEADER = socketHeader.h
LIBS = -lws2_32
DLL = 

$(TARGET):$(OBJS)
	$(CC) $(OBJS) $(LIBS) -o $(TARGET)

%.o:%.c $(HEADER)
	$(CC) -c $< -o $@


.PHONY: clean uninstall
clean:
	rm $(OBJS)

uninstall:
	rm $(TARGET)
	