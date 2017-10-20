# Makefile for NetworkAgent

# variables for building with
CXX			= c++
OBJ 		= WatchDog.o MonitoringAgent.o Logger.o
BIN			= bin/*
SRC_FILES	= src/*
H_FILES 	= src/*.h
O_FILES		= build/*.o
CPP_FILES 	= src/*.cpp

VPATH		= src
BUILDDIR	= build

# compiler flags
ARGS		= -Wall -Wextra -pedantic
LIBS		= -lcurl

# command shortcuts
RM			= rm -f

NetworkAgent: $(OBJ)
	$(CXX) -o bin/NetworkAgent $(ARGS) $(LIBS) *.o

$(BUILDDIR)/%.o: %.cpp
	$(CXX) -c $< -o $@

.PHONY install clean:
install:
	cp bin/NetworkAgent ~/Downloads
	chmod +x ~/Downloads/NetworkAgent

clean:
	$(RM) *.o
	$(RM) $(BIN)
