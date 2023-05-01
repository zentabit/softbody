main: main.c
	gcc main.c -o main.out $$(pkg-config allegro-5 allegro_main-5 allegro_font-5 allegro_primitives-5 --libs --cflags)

clean:
	rm *.out