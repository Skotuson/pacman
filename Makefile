CXX      = g++
LD       = g++
CXXFLAGS = -g -std=c++17 -Wall -pedantic
OUTPUT   = skotajir

all: $(OUTPUT) doc

compile: $(OUTPUT)

$(OUTPUT): src/main.o src/game/CGame.o src/game/CConfig.o src/maze/CMaze.o src/maze/CEmptyTile.o src/maze/CCoinTile.o src/maze/CWallTile.o\
		src/game/CController.o src/game/CRender.o src/entity/CEntity.o src/entity/CPacman.o src/entity/CGhost.o src/maze/CPelletTile.o src/entity/CBlinky.o \
		src/entity/CPinky.o src/entity/CInky.o src/entity/CClyde.o src/game/CGeometry.o src/maze/CTeleportTile.o
	$(LD) $(CXXFLAGS) -o $@ $^

valgrind: $(OUTPUT)
	valgrind ./$(OUTPUT)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f *.o $(OUTPUT) Makefile.d
	rm -f src/*.o
	rm -f src/entity/*.o
	rm -f src/game/*.o
	rm -f src/maze/*.o
	rm -rf doc/

doc:
	doxygen Doxyfile
 
run: $(OUTPUT)
	./$(OUTPUT)

-include Makefile.d

deps:
	$(CXX) -MM $(wildcard src/*cpp)        >> Makefile.d
	$(CXX) -MM $(wildcard src/game/*cpp)   >> Makefile.d
	$(CXX) -MM $(wildcard src/maze/*cpp)   >> Makefile.d
	$(CXX) -MM $(wildcard src/entity/*cpp) >> Makefile.d