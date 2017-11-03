// Header file for logger

using namespace std;

#ifndef LOGGER_H
#define LOGGER_H

// define our logging paths
// UNIX/POSIX based systems
#if !defined(_WIN32) && (defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__)) || defined(_POSIX_VERSION))
#include <unistd.h>
#define LOGPATH "/var/log/NetworkAgent.log"
#endif

// Windows
#if defined(_WIN64)
#define LOGPATH = "C:\\Program Files(x86)\\NetworkAgent\\log\\NetworkAgent.log"
#elif defined(_WIN32)
#define LOGPATH = "C:\\Program Files(x86)\\NetworkAgent\\log\\NetworkAgent.log"
#endif

class Logger
{

public:

    // VARIABLES
    string logUser;
    string logPath;

    // CONSTRUCTORS
    Logger( string user );
    Logger( string user, string path );

    // METHODS
    void log( string message );

private:

};

#endif
