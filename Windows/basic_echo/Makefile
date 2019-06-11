all: win_client.c
	gcc win_client.c -o win_client.exe -l ws2_32
#win_server.exe: win_server.c
	gcc win_server.c -o win_server.exe -l ws2_32

#win_client.o: win_client.c
#	gcc -c win_client.c
#win_server.o: win_server.c
#	gcc -c win_server.c

.PHONY: clean
clean:
	rm win_*.exe