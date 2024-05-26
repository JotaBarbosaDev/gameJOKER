run:
	gcc `pkg-config --cflags gtk+-3.0` -o main gtk_function.c UI/ui.c perguntas/perguntas.c user/users.c UI/ui_jogo.c UI/create_pergunta.c UI/edit_pergunta.c UI/ver_perguntas.c UI/user_UI.c  main.c `pkg-config --libs gtk+-3.0` -Wno-deprecated-declarations 
	./main