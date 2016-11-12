server-objs:=ntld_test_server.o ntld.o xmlparse.o
client-objs:=ntld_test_client.o ntld.o 
all:server_tcp client_tcp
%.o:%.c
	$(CC) -c $<
server_tcp:$(server-objs)
	$(CC) -o $@ $(server-objs)
client_tcp:$(client-objs)
	$(CC) -o $@ $(client-objs)
clean:
	rm *.o server_tcp client_tcp