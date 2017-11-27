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

struct connection reporter;

// Constructor
Reporter::Reporter( string server, string name, string path )
{
    hostname = server;
    trustedName = name;
    CAFilePath = path;

    // set reporter stuff    
    reporter.port = 5556;
    reporter.server = (char*)hostname.c_str();

    this->connect();
}

// close out the reporter
void Reporter::deinit( )
{
    this->disconnect();
}

// reports some information to a server
void Reporter::report( int type, string status )
{
    string intToStr = to_string(type) + status;
    char buff[20];
    memset(buff, 0, sizeof(char) * 20);
    memcpy(buff, intToStr.c_str(), (intToStr.length() < 20)? intToStr.length() : sizeof(char) * 20);

    int bytes = intToStr.length();

    // Send the info
    tls_send(&reporter, buff, bytes);
    tls_recv(&reporter, buff, bytes);
}

// connect to server
void Reporter::connect( )
{
    // open the connection    
    open_tcp(&reporter);
    connect_TLS(&reporter, (char*)CAFilePath.c_str(), (char*)trustedName.c_str(), trustedName.length());
}

// disdonnect from server
void Reporter::disconnect( )
{
    // Close the connections
    disconnect_tls(&reporter);
    close_tcp(&reporter);
    deinit_tls();
}
