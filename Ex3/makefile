# Email: shanig7531@gmail.com

CXX = clang++ # Compiler
CXXFLAGS = -std=c++17 -Wall -g # Flags
INCLUDES = -I./src -I./Test -I./GUI
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

all: Main

Main: Player.o Game.o Spy.o Merchant.o General.o Judge.o Baron.o Governor.o windowManager.o Button.o Main.o
	$(CXX) $(CXXFLAGS) -o Main Player.o Game.o Spy.o Merchant.o General.o Judge.o Baron.o Governor.o windowManager.o Button.o Main.o $(LDFLAGS)

Player.o: src/Player.cpp src/Player.hpp src/Merchant.hpp src/Baron.hpp src/Game.hpp
	$(CXX) $(CXXFLAGS) -c src/Player.cpp -o Player.o

Game.o: src/Game.cpp src/Game.hpp src/Merchant.hpp src/Baron.hpp src/Spy.hpp src/General.hpp src/Judge.hpp src/Governor.hpp src/Player.hpp
	$(CXX) $(CXXFLAGS) -c src/Game.cpp -o Game.o

Spy.o: src/Spy.cpp src/Spy.hpp src/Game.hpp src/Player.hpp
	$(CXX) $(CXXFLAGS) -c src/Spy.cpp -o Spy.o

Merchant.o: src/Merchant.cpp src/Merchant.hpp src/Game.hpp src/Player.hpp
	$(CXX) $(CXXFLAGS) -c src/Merchant.cpp -o Merchant.o

General.o: src/General.cpp src/General.hpp src/Game.hpp src/Player.hpp
	$(CXX) $(CXXFLAGS) -c src/General.cpp -o General.o

Judge.o: src/Judge.cpp src/Judge.hpp src/Game.hpp src/Player.hpp
	$(CXX) $(CXXFLAGS) -c src/Judge.cpp -o Judge.o

Baron.o: src/Baron.cpp src/Baron.hpp src/Game.hpp
	$(CXX) $(CXXFLAGS) -c src/Baron.cpp -o Baron.o

Governor.o: src/Governor.cpp src/Governor.hpp src/Game.hpp src/Player.hpp
	$(CXX) $(CXXFLAGS) -c src/Governor.cpp -o Governor.o

windowManager.o: GUI/windowManager.cpp GUI/windowManager.hpp GUI/Button.hpp
	$(CXX) $(CXXFLAGS) -c GUI/windowManager.cpp -o windowManager.o

Button.o: GUI/Button.cpp GUI/Button.hpp
	$(CXX) $(CXXFLAGS) -c GUI/Button.cpp -o Button.o

Main.o: GUI/main.cpp
	$(CXX) $(CXXFLAGS) -c GUI/main.cpp -o Main.o

tests: Tests/Tests.cpp Player.o Game.o Spy.o Merchant.o General.o Judge.o Baron.o Governor.o
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o tests Tests/Tests.cpp Player.o Game.o Spy.o Merchant.o General.o Judge.o Baron.o Governor.o

test: tests
	./tests

valgrind: Main
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./Main

clean:
	rm -f *.o Main Test tests

.PHONY: all clean test
