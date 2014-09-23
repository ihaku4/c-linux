gcc-m:
	gcc stringutil.c 25-2-11-ex3-gcc-M.c
simple-shell:
	gcc stringutil.c 30-5-ex-simple-shell.c
clean:
	@echo "cleaning project"
	-rm a.out *.o
	@echo "clean complete"
