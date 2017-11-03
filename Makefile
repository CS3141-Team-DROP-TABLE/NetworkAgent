# Makefile for NetworkAgent

# variables for building with
C			= gcc
CXX			= c++
VPATH		= src
BPATH		= build
OBJ 		= WatchDog.o MonitoringAgent.o Logger.o Reporter.o ServerConnect.o
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

Reporter.o: Reporter.cpp
	$(CXX) -c $< $(INCL) -Ilib/CServerLibraries/include -o $(BPATH)/Reporter.o

ServerConnect.o: serverConnect.c
	$(C) -c lib/CServerLibraries/$< -Ilib/CServerLibraries/include -o $(BPATH)/ServerConnect.o

# extra options
.PHONY install clean:
install:
	chmod +x bin/NetworkAgent

clean:
	$(RM) $(O_FILES)
	$(RM) $(BIN)
