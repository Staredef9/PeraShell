perashell: main.c
	gcc -g -o perashell main.c builtins.c parse.c executor.c
clean:
	rm perashell
