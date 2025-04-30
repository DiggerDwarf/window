EXE 		= window

SRC 		= $(wildcard src/*.cpp)
OBJ 		= $(subst src, build, $(patsubst %.cpp, %.o, $(SRC)))

DBG 		= 	# debug flags

INCLUDE 	= -I include
LIB 		= -Llib -lglew32 -lopengl32 -lgdi32
EXTRA		= -Werror -Wall -DGLEW_STATIC
STATIC  	= -static


all: shared static

remake: clean all

clean:
	rm -f $(subst build/, build/, $(OBJ))

build/%.o: src/%.cpp
	g++ $(INCLUDE) -c src/$*.cpp -o build/$*.o $(DBG) $(EXTRA) -DSW_BUILD -DSW_DEBUG


rc_file/%:
	windres src/$*.rc -O coff -o build/$*.res

demo/%:
	g++ $(INCLUDE) -c examples/$*.cpp -o examples/$*.o $(EXTRA)
	g++ examples/$*.o -Llib -lsw32-shared -lglew32 -lopengl32 -o examples/$*.exe
	rm examples/$*.o
	./examples/$*.exe

static: $(OBJ)
	ar rs lib/libsw32-static.a $(OBJ)

shared: $(OBJ)
	g++ $(OBJ) $(LIB) -shared -o libsw32.dll -Wl,--out-implib,lib/libsw32-shared.a

.PHONY: all remake clean static shared demo/%
