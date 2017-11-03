// Team Software Project Fall 2017
// Team "; DROP TABLE team_names;
// Reporter: reports information to a central server

// C libraries
#include <cstddef>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>

// Headers
#include "Reporter.h"

// Lib includes
#include "serverConnect.h"

using namespace std;

// Constructor
Reporter::Reporter( string server, string name, string path )
{
    hostname = server;
    trustedName = name;
    CAFilePath = path;
}

// reports some information to a server
void Reporter::report( int type, int status )
{
    string intToStr = to_string(type) + to_string(status);
    char buff[20] = intToStr.copy(buff, intToStr.length()+1);

    int bytes = 0;

    // Connect to the central server
    struct connection reporter;
    reporter.port = 5556;
    reporter.server = hostname.c_str();
    
    open_tcp(&reporter);
    connect_TLS(&reporter, CAFilePath.c_str(), trustedName.c_str(), trustedName.length());

    // Send the info
    tls_send(&reporter, buff, bytes);
    tld_recv(&reporter, buff, bytes);

    // Close the connections
    disconnect_tls(&reporter);
    close_tcp(&reporter);
    deinit_tls();
}
