# Makefile for NetworkAgent

# variables for building with
CXX			= c++
VPATH		= src
BPATH		= build
OBJ 		= WatchDog.o MonitoringAgent.o Logger.o
BIN			= bin/*
CPP_FILES 	= src/*.cpp
H_FILES 	= include/*.h
O_FILES		= build/*.o

# compiler flags
ARGS		= -std=c++11 -Wall -Wextra -pedantic
LIBS		= -lcurl
INCL		= -Iinclude

# command shortcuts
RM			= rm -f

# building rules
NetworkAgent: $(OBJ)
	$(CXX) -o bin/NetworkAgent $(ARGS) $(LIBS) $(O_FILES)

WatchDog.o: WatchDog.cpp
	$(CXX) -c $< $(INCL) -o $(BPATH)/WatchDog.o

MonitoringAgent.o: MonitoringAgent.cpp
	$(CXX) -c $< $(INCL) -o $(BPATH)/MonitoringAgent.o

Logger.o: Logger.cpp
	$(CXX) -c $< $(INCL) -o $(BPATH)/Logger.o

# extra options
.PHONY install clean:
install:
	chmod +x bin/NetworkAgent

clean:
	$(RM) $(O_FILES)
	$(RM) $(BIN)
