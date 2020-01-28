#
# Variablen helfen in Makefiles copy&paste zu verringern und die "Rezepte"
# uebersichtlicher zu gestalten.
#

CC = gcc
CFLAGS = `sdl2-config --libs --cflags -lSDL2 -lSDLImage2` -ggdb3 -O0 --std=c99 -Wall -lSDL2_image -lm 

PAC-entity.exe:

	$(CC) $(CFLAGS) -o PAC-entity.out Main.c
	
	./PAC-entity.out