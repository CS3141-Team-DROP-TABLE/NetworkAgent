// Header file for logger

#ifndef LOGGER_H
#define LOGGER_H

using namespace std;

class Logger
{

public:

    // VARIABLES
    string logUser;
    string logPath;

    // CONSTRUCTORS
    Logger( string user, string path );

    // METHODS
    void log( string message );

private:

};

#endif
