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

// init the objects for use
Logger agentLogger( "Agent   " );

MonitoringAgent::MonitoringAgent( string assignedName, string assignedIP ) 
{
    name = assignedName;
    ip = assignedIP;

    // initialize curl with the networking stack
    // this is for some other methods
    curl_global_init(CURL_GLOBAL_ALL);
}

// check if the host is connected to the internet using curl
// this tries to get to google
int MonitoringAgent::checkConnectivity()
{
    agentLogger.log( "Checking network connectivity..." );

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
            agentLogger.log( "Network connection found!" );
            status = 1;
        }
        else
        {
            agentLogger.log( "Unable to connect to network." );
            status = 0;
        }
   
        // clean any leftovers
        curl_easy_cleanup(curl);
    }

    return status;
}

// checks bandwidth thoroughput of the host
int MonitoringAgent::checkBandwidth() 
{
    agentLogger.log( "Checking bandwidth capacity..." );

    return 0;
}

// checks network latency of the host
int MonitoringAgent::checkLatency() 
{
    agentLogger.log( "Checking network latency..." );

    return 0;
}

// checks the current processing load of the host
int MonitoringAgent::checkCPU() 
{
    agentLogger.log( "Checking CPU load..." );

    return 0;
}
