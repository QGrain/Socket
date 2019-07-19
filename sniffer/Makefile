CC = gcc
target = sniffer
source = sniffer.c
obj = sniffer.o
header = socketHeader.h
lib = ws2_32
dll = 

$(target):$(obj)
	$(CC) $(obj) -l $(lib) -o $(target)

%.o:%.c $(header)
	$(CC) -c $< -o $@

.PHONY: clean
clean:
	rm $(obj)
	