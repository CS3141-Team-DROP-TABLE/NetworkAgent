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
string MonitoringAgent::checkConnectivity()
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

    return to_string(status);
}

// helper method for bandwidth check
static size_t WriteCallback(void *ptr, size_t size, size_t nmemb, void *data)
{
    /* we are not interested in the downloaded bytes itself,
    so we only return the size we would have saved ... */ 
    (void)ptr;  /* unused */ 
    (void)data; /* unused */ 

    return (size_t)(size * nmemb);
}

// checks bandwidth thoroughput of the host
string MonitoringAgent::checkBandwidth() 
{
    agentLogger.log( "Checking bandwidth capacity..." );

    double bandwidth = 0.0;

    // Options for the files to fetch for the test
    string base_url = "https://tsp.bilderback.me/bw_test/";
    string file_1M = "1M.bin";
    string file_2M = "2M.bin";
    string file_5M = "5M.bin";
    string file_10M = "10M.bin";
    string file_20M = "20M.bin";
    string file_50M = "50M.bin";
    string file_100M = "100M.bin";

    // initialize curl
    curl = curl_easy_init();

    if( curl )
    {
        // set curl options
        curl_easy_setopt(curl, CURLOPT_URL, "https://tsp.bilderback.me/bw_test/100M.bin" );
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);

        // do the request
        httpResult = curl_easy_perform(curl);

        // check request response
        if( httpResult == CURLE_OK )
        {
            /* check for average download speed */ 
            httpResult = curl_easy_getinfo(curl, CURLINFO_SPEED_DOWNLOAD, &bandwidth);
            // since the speed from curl is in bytes/sec we need to change to megabits/sec
            bandwidth = (bandwidth / 1024 / 1024) * 8; 

            string bandwidthStr = to_string(bandwidth);
            agentLogger.log( "Current bandwidth: " + bandwidthStr );
        }
        else
        {
            agentLogger.log( "Unable to perform bandwidth test. Connection failed." );
            bandwidth = 0.0;
        }
   
        // clean any leftovers
        curl_easy_cleanup(curl);
    }

    return to_string(bandwidth);
}

// checks network latency of the host
string MonitoringAgent::checkLatency() 
{
    agentLogger.log( "Checking network latency..." );

    return "0";
}

// checks the current processing load of the host
string MonitoringAgent::checkCPU() 
{
    agentLogger.log( "Checking CPU load..." );

    return "0";
}
