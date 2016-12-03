#------------------------------------------------------------------------------#
# This makefile was generated by 'cbp2make' tool rev.147                       #
#------------------------------------------------------------------------------#


WORKDIR = `pwd`

CC = gcc
CXX = g++
AR = ar
LD = g++
WINDRES = windres

INC = 
CFLAGS = -Wall
RESINC = 
LIBDIR = 
LIB = -lSDL2
LDFLAGS = 

INC_DEBUG = $(INC)
CFLAGS_DEBUG = $(CFLAGS) -g
RESINC_DEBUG = $(RESINC)
RCFLAGS_DEBUG = $(RCFLAGS)
LIBDIR_DEBUG = $(LIBDIR)
LIB_DEBUG = $(LIB)
LDFLAGS_DEBUG = $(LDFLAGS)
OBJDIR_DEBUG = obj/Debug
DEP_DEBUG = 
OUT_DEBUG = bin/Debug/Snake

INC_RELEASE = $(INC)
CFLAGS_RELEASE = $(CFLAGS) -O2
RESINC_RELEASE = $(RESINC)
RCFLAGS_RELEASE = $(RCFLAGS)
LIBDIR_RELEASE = $(LIBDIR)
LIB_RELEASE = $(LIB)
LDFLAGS_RELEASE = $(LDFLAGS) -s
OBJDIR_RELEASE = obj/Release
DEP_RELEASE = 
OUT_RELEASE = bin/Release/Snake

OBJ_DEBUG = $(OBJDIR_DEBUG)/audio.o $(OBJDIR_DEBUG)/jogo.o $(OBJDIR_DEBUG)/main.o $(OBJDIR_DEBUG)/menu.o $(OBJDIR_DEBUG)/opcoes.o $(OBJDIR_DEBUG)/ranking.o $(OBJDIR_DEBUG)/render.o

OBJ_RELEASE = $(OBJDIR_RELEASE)/audio.o $(OBJDIR_RELEASE)/jogo.o $(OBJDIR_RELEASE)/main.o $(OBJDIR_RELEASE)/menu.o $(OBJDIR_RELEASE)/opcoes.o $(OBJDIR_RELEASE)/ranking.o $(OBJDIR_RELEASE)/render.o

all: release

clean: clean_debug clean_release

before_debug: 
	test -d bin/Debug || mkdir -p bin/Debug
	test -d $(OBJDIR_DEBUG) || mkdir -p $(OBJDIR_DEBUG)

after_debug: 

debug: before_debug out_debug after_debug

out_debug: before_debug $(OBJ_DEBUG) $(DEP_DEBUG)
	$(LD) $(LIBDIR_DEBUG) -o $(OUT_DEBUG) $(OBJ_DEBUG)  $(LDFLAGS_DEBUG) $(LIB_DEBUG)

$(OBJDIR_DEBUG)/audio.o: audio.c
	$(CC) $(CFLAGS_DEBUG) $(INC_DEBUG) -c audio.c -o $(OBJDIR_DEBUG)/audio.o

$(OBJDIR_DEBUG)/jogo.o: jogo.c
	$(CC) $(CFLAGS_DEBUG) $(INC_DEBUG) -c jogo.c -o $(OBJDIR_DEBUG)/jogo.o

$(OBJDIR_DEBUG)/main.o: main.c
	$(CC) $(CFLAGS_DEBUG) $(INC_DEBUG) -c main.c -o $(OBJDIR_DEBUG)/main.o

$(OBJDIR_DEBUG)/menu.o: menu.c
	$(CC) $(CFLAGS_DEBUG) $(INC_DEBUG) -c menu.c -o $(OBJDIR_DEBUG)/menu.o

$(OBJDIR_DEBUG)/opcoes.o: opcoes.c
	$(CC) $(CFLAGS_DEBUG) $(INC_DEBUG) -c opcoes.c -o $(OBJDIR_DEBUG)/opcoes.o

$(OBJDIR_DEBUG)/ranking.o: ranking.c
	$(CC) $(CFLAGS_DEBUG) $(INC_DEBUG) -c ranking.c -o $(OBJDIR_DEBUG)/ranking.o

$(OBJDIR_DEBUG)/render.o: render.c
	$(CC) $(CFLAGS_DEBUG) $(INC_DEBUG) -c render.c -o $(OBJDIR_DEBUG)/render.o

clean_debug: 
	rm -f $(OBJ_DEBUG) $(OUT_DEBUG)
	rm -rf bin/Debug
	rm -rf $(OBJDIR_DEBUG)

before_release: 
	test -d bin/Release || mkdir -p bin/Release
	test -d $(OBJDIR_RELEASE) || mkdir -p $(OBJDIR_RELEASE)

after_release: 

release: before_release out_release after_release

out_release: before_release $(OBJ_RELEASE) $(DEP_RELEASE)
	$(LD) $(LIBDIR_RELEASE) -o $(OUT_RELEASE) $(OBJ_RELEASE)  $(LDFLAGS_RELEASE) $(LIB_RELEASE)

$(OBJDIR_RELEASE)/audio.o: audio.c
	$(CC) $(CFLAGS_RELEASE) $(INC_RELEASE) -c audio.c -o $(OBJDIR_RELEASE)/audio.o

$(OBJDIR_RELEASE)/jogo.o: jogo.c
	$(CC) $(CFLAGS_RELEASE) $(INC_RELEASE) -c jogo.c -o $(OBJDIR_RELEASE)/jogo.o

$(OBJDIR_RELEASE)/main.o: main.c
	$(CC) $(CFLAGS_RELEASE) $(INC_RELEASE) -c main.c -o $(OBJDIR_RELEASE)/main.o

$(OBJDIR_RELEASE)/menu.o: menu.c
	$(CC) $(CFLAGS_RELEASE) $(INC_RELEASE) -c menu.c -o $(OBJDIR_RELEASE)/menu.o

$(OBJDIR_RELEASE)/opcoes.o: opcoes.c
	$(CC) $(CFLAGS_RELEASE) $(INC_RELEASE) -c opcoes.c -o $(OBJDIR_RELEASE)/opcoes.o

$(OBJDIR_RELEASE)/ranking.o: ranking.c
	$(CC) $(CFLAGS_RELEASE) $(INC_RELEASE) -c ranking.c -o $(OBJDIR_RELEASE)/ranking.o

$(OBJDIR_RELEASE)/render.o: render.c
	$(CC) $(CFLAGS_RELEASE) $(INC_RELEASE) -c render.c -o $(OBJDIR_RELEASE)/render.o

clean_release: 
	rm -f $(OBJ_RELEASE) $(OUT_RELEASE)
	rm -rf bin/Release
	rm -rf $(OBJDIR_RELEASE)

.PHONY: before_debug after_debug clean_debug before_release after_release clean_release

