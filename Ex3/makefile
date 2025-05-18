# Compiler and Flags
CXX = clang++
CXXFLAGS = -std=c++17 -Wall -g
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

# Source Files
SRC = src/Game.cpp src/Player.cpp src/Governor.cpp src/Baron.cpp src/General.cpp src/Merchant.cpp src/Judge.cpp src/Spy.cpp
GUI = GUI/GameGUI.cpp GUI/Button.cpp GUI/windowManager.cpp GUI/main.cpp
TEST_SRC = Test/Tests.cpp
TEST_HEADERS = Test/doctest.h

# Output Names
EXEC_MAIN = coup_game
EXEC_TEST = test_player

# Default Target
all: Main

# Compile and run the game
Main: $(SRC) $(GUI)
	$(CXX) $(CXXFLAGS) -Isrc -IGUI -ITest $(SRC) $(GUI) -o $(EXEC_MAIN) $(LDFLAGS)
	./$(EXEC_MAIN)

# Compile and run the unit tests
test: $(SRC) $(TEST_SRC)
	$(CXX) $(CXXFLAGS) -Isrc -ITest $(SRC) $(TEST_SRC) -o $(EXEC_TEST)
	./$(EXEC_TEST)

# Clean build artifacts
clean:
	rm -f $(EXEC_MAIN) $(EXEC_TEST)
