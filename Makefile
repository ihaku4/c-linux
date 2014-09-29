tcp: server client
udp: udp-server udp-client
gcc-m:
	gcc stringutil.c 25-2-11-ex3-gcc-M.c
simple-shell:
	gcc stringutil.c 30-5-ex-simple-shell.c
server:
	gcc wrap.c 37-2-server.c -o server.out
client:
	gcc wrap.c 37-2-client.c -o client.out
udp-server:
	gcc wrap.c 37-3-udp-server.c -o server.out
udp-client:
	gcc wrap.c 37-3-udp-client.c -o client.out
web-server:
	gcc wrap.c 37-5-web-server.c -o web-server.out
clean:
	@echo "cleaning project"
	-rm a.out *.o *.out
	@echo "clean complete"
