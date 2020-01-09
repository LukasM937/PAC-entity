#
# Variablen helfen in Makefiles copy&paste zu verringern und die "Rezepte"
# uebersichtlicher zu gestalten.
#

CC = gcc
CFLAGS = -std=c99 -pedantic -Wall -Wextra
SDLFLAG = `sdl2-config --cflags --libs`
OUT = PAC-entity.out
EXE = PAC-entity.out

# ifeq ($(OS),Windows_NT)
#     CCFLAGS += -D WIN32
#     ifeq ($(PROCESSOR_ARCHITEW6432),AMD64)
#         CCFLAGS += -D AMD64
#     else
#         ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
#             CCFLAGS += -D AMD64
#         endif
#         ifeq ($(PROCESSOR_ARCHITECTURE),x86)
#             CCFLAGS += -D IA32
#         endif
#     endif
# else
#     UNAME_S := $(shell uname -s)
#     ifeq ($(UNAME_S),Linux)
#         CCFLAGS += -D LINUX
#     endif
#     ifeq ($(UNAME_S),Darwin)
#         CCFLAGS += -D OSX
#     endif
# endif

# Rezept wird mit `make PAC-entity.out` aufgerufen, Windows-Nutzer muessen vor
# `./Soduku2.out` ggf. das `./` entfernen.

PAC-entity.exe:

	$(CC) $(CFLAGS) -o PAC-entity.out Main.c $(SDLFLAG)
	
	./PAC-entity.out