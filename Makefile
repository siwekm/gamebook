
CXX=g++
CXXFLAGS=-Wall -pedantic -g -std=c++17
LD=g++
LDFLAGS=-lncurses
EXECUTABLE=siwekmar

SRC_DIR=src



all: ${EXECUTABLE} doc

run: ${EXECUTABLE}
	./${EXECUTABLE}

compile: ${EXECUTABLE}

doc: Doxyfile ${SRC_DIR}/*
	doxygen Doxyfile

${EXECUTABLE}: main.o Entity.o Game.o Inventory.o Item.o Location.o Player.o PlayerCreator.o World.o Saver.o Potion.o Weapon.o
	${LD} ${LDFLAGS} $^ -o ${EXECUTABLE}

Entity.o: ${SRC_DIR}/Entity.cpp ${SRC_DIR}/Entity.h
	${CXX} ${CXXFLAGS} -c $< -o $@

Game.o: ${SRC_DIR}/Game.cpp ${SRC_DIR}/Game.h ${SRC_DIR}/World.h ${SRC_DIR}/Entity.h ${SRC_DIR}/Location.h ${SRC_DIR}/Item.h ${SRC_DIR}/Player.h ${SRC_DIR}/Inventory.h ${SRC_DIR}/Weapon.h ${SRC_DIR}/Potion.h ${SRC_DIR}/PlayerCreator.h ${SRC_DIR}/Saver.h
	${CXX} ${CXXFLAGS} -c $< -o $@

Inventory.o: ${SRC_DIR}/Inventory.cpp ${SRC_DIR}/Inventory.h
	${CXX} ${CXXFLAGS} -c $< -o $@

Item.o: ${SRC_DIR}/Item.cpp ${SRC_DIR}/Item.h ${SRC_DIR}/Player.h ${SRC_DIR}/Entity.h ${SRC_DIR}/Inventory.h
	${CXX} ${CXXFLAGS} -c $< -o $@

Location.o: ${SRC_DIR}/Location.cpp ${SRC_DIR}/Location.h ${SRC_DIR}/Entity.h ${SRC_DIR}/Item.h ${SRC_DIR}/Player.h ${SRC_DIR}/Inventory.h ${SRC_DIR}/Weapon.h ${SRC_DIR}/Potion.h
	${CXX} ${CXXFLAGS} -c $< -o $@

main.o: ${SRC_DIR}/main.cpp ${SRC_DIR}/PlayerCreator.h ${SRC_DIR}/Player.h ${SRC_DIR}/Entity.h ${SRC_DIR}/Inventory.h ${SRC_DIR}/Game.h ${SRC_DIR}/World.h ${SRC_DIR}/Location.h ${SRC_DIR}/Item.h ${SRC_DIR}/Weapon.h ${SRC_DIR}/Potion.h
	${CXX} ${CXXFLAGS} -c $< -o $@

Player.o: ${SRC_DIR}/Player.cpp ${SRC_DIR}/Player.h ${SRC_DIR}/Entity.h ${SRC_DIR}/Inventory.h
	${CXX} ${CXXFLAGS} -c $< -o $@

PlayerCreator.o: ${SRC_DIR}/PlayerCreator.cpp ${SRC_DIR}/PlayerCreator.h ${SRC_DIR}/Player.h ${SRC_DIR}/Entity.h ${SRC_DIR}/Inventory.h
	${CXX} ${CXXFLAGS} -c $< -o $@

Potion.o: ${SRC_DIR}/Potion.cpp ${SRC_DIR}/Potion.h ${SRC_DIR}/Player.h ${SRC_DIR}/Entity.h ${SRC_DIR}/Inventory.h ${SRC_DIR}/Item.h
	${CXX} ${CXXFLAGS} -c $< -o $@

Saver.o: ${SRC_DIR}/Saver.cpp ${SRC_DIR}/Saver.h ${SRC_DIR}/Player.h ${SRC_DIR}/Entity.h ${SRC_DIR}/Inventory.h ${SRC_DIR}/Item.h ${SRC_DIR}/Weapon.h ${SRC_DIR}/Potion.h
	${CXX} ${CXXFLAGS} -c $< -o $@

Weapon.o: ${SRC_DIR}/Weapon.cpp ${SRC_DIR}/Weapon.h ${SRC_DIR}/Item.h ${SRC_DIR}/Player.h ${SRC_DIR}/Entity.h ${SRC_DIR}/Inventory.h
	${CXX} ${CXXFLAGS} -c $< -o $@

World.o: ${SRC_DIR}/World.cpp ${SRC_DIR}/World.h ${SRC_DIR}/Entity.h ${SRC_DIR}/Location.h ${SRC_DIR}/Item.h ${SRC_DIR}/Player.h ${SRC_DIR}/Inventory.h ${SRC_DIR}/Weapon.h ${SRC_DIR}/Potion.h
	${CXX} ${CXXFLAGS} -c $< -o $@

.PHONY: clean all compile run
clean:
	rm -f *.o
	rm ${EXECUTABLE}
	rm -fr doc

