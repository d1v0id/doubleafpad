doubleafpad: main.c interface.c settings.c texttools.c
	gcc main.c interface.c settings.c texttools.c -o doubleafpad `pkg-config --libs --cflags gtk+-2.0`
