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
LIBS		= -lcurl -lgnutls
INCL		= -Iinclude
SERVLIB		= -Ilib/CServerLibraries/include
SERVSRC		= lib/CServerLibraries

# command shortcuts
RM			= rm -f

# building rules
NetworkAgent: $(OBJ)
	$(CXX) -o bin/NetworkAgent $(ARGS) $(LIBS) $(SERVLIB) $(O_FILES)

WatchDog.o: WatchDog.cpp
	$(CXX) -c $< $(INCL) $(SERVLIB) -o $(BPATH)/WatchDog.o

MonitoringAgent.o: MonitoringAgent.cpp
	$(CXX) -c $< $(INCL) -o $(BPATH)/MonitoringAgent.o

Logger.o: Logger.cpp
	$(CXX) -c $< $(INCL) -o $(BPATH)/Logger.o

Reporter.o: Reporter.cpp
	$(CXX) -c $< $(INCL) $(SERVLIB) -o $(BPATH)/Reporter.o

ServerConnect.o:
	$(CXX) -c $(SERVSRC)/serverConnect.c $(SERVLIB) -o $(BPATH)/ServerConnect.o

#ConfigLoader.o:
#	$(CXX) -c $(SERVSRC)/configLoader.c $(SERVLIB) -o $(BPATH)/ConfigLoader.o

#StringMap.o:
#	$(CXX) -c $(SERVSRC)/stringMap.c $(SERVLIB) -o $(BPATH)/StringMap.o

#AVL.o:
#	$(CXX) -c $(SERVSRC)/AVL.c $(SERVLIB) -o $(BPATH)/AVL.o

# extra options
.PHONY install clean:
install:
	chmod +x bin/NetworkAgent
	cp bin/NetworkAgent /usr/local/bin/NetworkAgent

clean:
	$(RM) $(O_FILES)
	$(RM) $(BIN)
