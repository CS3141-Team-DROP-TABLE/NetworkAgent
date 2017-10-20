// Team Software Project Fall 2017
// Team "; DROP TABLE team_names;
// Monitoring Agent: The agent lives on a host and monitors different processes and reports back to the central server.

// C libraries
#include <cstddef>
#include <iostream>
#include <cstring>

// Headers
#include "MonitoringAgent.h"
#include "Logger.h"

// external
#include <curl/curl.h>

using namespace std;

// init curl stuff
CURL *curl;
CURLcode httpResult;

MonitoringAgent::MonitoringAgent( string assignedName, string assignedIP, string assignedReportingServer, string assignedLogPath ) 
{

    name = assignedName;
    ip = assignedIP;
    reportingServer = assignedReportingServer;
    logPath = assignedLogPath;

    // initialize curl with the networking stack
    // this is for some other methods
    curl_global_init(CURL_GLOBAL_ALL);

    // get our logging object here
    Logger logger( "Agent   ", logPath );
}

// check if the host is connected to the internet using curl
// this tries to get to google
int MonitoringAgent::checkConnectivity()
{
    // get our logging object here
    Logger logger( "Agent   ", logPath );

    logger.log( "Checking network connectivity..." );

    int status = 0;

    // initialize curl
    curl = curl_easy_init();

    // Based on the example found at https://curl.haxx.se/libcurl/c/simple.html
    // This should work in Windows...
    if( curl )
    {
        // set the options for the request
        curl_easy_setopt(curl, CURLOPT_URL, "https://www.google.com");
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_CONNECT_ONLY, 1L);
        curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);

        // do the request
        httpResult = curl_easy_perform(curl);

        // check request response
        if( httpResult == CURLE_OK )
        {
            logger.log( "Network connection found!" );
            //this->report();
            status = 1;
        }
        else
        {
            logger.log( "Unable to connect to network." );
            //this->report();
            status = 0;
        }
   
        // clean any leftovers
        curl_easy_cleanup(curl);
    }

    return status;
}

// checks bandwidth thoroughput of the host
void MonitoringAgent::checkBandwidth() 
{
    // get our logging object here
    Logger logger( "Agent   ", logPath );

    logger.log( "Checking bandwidth capacity..." );
    //this->report();
}

// checks network latency of the host
void MonitoringAgent::checkLatency() 
{
    // get our logging object here
    Logger logger( "Agent   ", logPath );

    logger.log( "Checking network latency..." );
    //this->report();
}

// checks the current processing load of the host
void MonitoringAgent::checkCPU() 
{
    // get our logging object here
    Logger logger( "Agent   ", logPath );

    logger.log( "Checking CPU load..." );
    //this->report();
}

// reports all data to the central server
void MonitoringAgent::report( string server ) 
{
    // get our logging object here
    Logger logger( "Agent   ", logPath );

    logger.log( "Sending data to " + server + "..." ); 
}
