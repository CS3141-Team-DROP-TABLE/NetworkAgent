// Team Software Project Fall 2017
// Team "; DROP TABLE team_names;
// Logger: logs information from other parts of the agent

// C libraries
#include <cstddef>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <ctime>

// Headers
#include "Logger.h"

using namespace std;

// Constructor
Logger::Logger( string user )
{
    logUser = user;
    logPath = LOGPATH;
}

Logger::Logger( string user, string path )
{
    logUser = user;
    logPath = path;
}

// Logs a message to file
void Logger::log( string message ) 
{
    // get the current date and time
    time_t currentTime = time(NULL);
    char now[30];
    strftime(now, 30, "[ %D ] %T", localtime(&currentTime));
    string logDate(now);

    // Open up the log file to write to
    // Since this is a log the file gets appended
    ofstream logFile;
    logFile.open(logPath, ios_base::app);
    if ( !logFile )
    {
        cout << "Unable to open " << logPath << endl;
        exit( 1 );
    }
    
    logFile << logDate << " -- " + logUser + "-- " + message << endl;
    logFile.close();
}