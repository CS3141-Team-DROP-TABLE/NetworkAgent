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

Logger::Logger( string user, string path )
{
    logUser = user;
    logPath = path;
}

void Logger::log( string message ) 
{
    // get the current date and time
    time_t currentTime = time(0);
    tm *lTime = localtime(&currentTime);

    // Open up the log file to write to
    // Since this is a log the file gets appended
    ofstream logFile;
    logFile.open(logPath, ios_base::app);
    if ( !logFile )
    {
        cout << "Unable to open " << logPath << endl;
        exit( 1 );
    }

    logFile << "[ " << lTime->tm_mday << "/" << 1 + lTime->tm_mon << "/" << 1900 + lTime->tm_year << " ] "
            << 1 + lTime->tm_hour << ":" << 1 + lTime->tm_min << ":" << 1 + lTime->tm_sec
            << " -- " + logUser + "-- " << message << endl;
    logFile.close();
}