perashell: main.c
	gcc -o perashell main.c builtins.c parse.c executor.c
clean:
	rm perashell
