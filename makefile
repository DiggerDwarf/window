EXE 		= window

SRC 		= $(wildcard src/*.cpp)
OBJ 		= $(subst src, build, $(patsubst %.cpp, %.o, $(SRC)))

DBG 		= 	# debug flags

INCLUDE 	= -I include
LIB 		= -lgdi32
EXTRA		= -Werror -Wall
STATIC  	= -static

all: link

remake: clean all

kaboom/%:	# if I ever need to integrate a file
	objcopy -I binary -O elf64-x86-64 obj/$*.obj build/$*.o

run:
	$(EXE)

clean:
	rm $(subst build/, build\, $(OBJ))

build/%.o: src/%.cpp
	g++ $(INCLUDE) -c src/$*.cpp -o build/$*.o $(DBG) $(EXTRA)

link: $(OBJ)
	g++ $(OBJ) build/check.res -o $(EXE) $(LIB) $(STATIC) $(DBG) $(EXTRA)

rc_file/%:
	windres src/$*.rc -O coff -o build/$*.res

test:
	g++ 