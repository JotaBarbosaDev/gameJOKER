run:
	gcc `pkg-config --cflags gtk+-3.0` -o main gtk_function.c ui.c main.c `pkg-config --libs gtk+-3.0`
	./main