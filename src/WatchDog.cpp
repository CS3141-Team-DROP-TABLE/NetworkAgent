// Team Software Project Fall 2017
// Team "; DROP TABLE team_names;
// Watch Dog: uses the Monitoring Agent to constantly check the host it's running on.

// C libraries
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <csignal>
#include <unistd.h>

// headers
#include "MonitoringAgent.h"
#include "Logger.h"

using namespace std;

// variables to set later on
string name;
string ip;
string reportingServer;
string logPath = "";

// method to watch for signals
void signalWatcher( int signum )
{

    Logger exitLogger( "Daemon  ", logPath );

    cout << "\n\nSignal received, exiting WatchDog..." << endl;
    exitLogger.log( "Signal received, exiting WatchDog..." );
    exit( signum );
}

int main( int argc, char* argv[] ) 
{

    // read in the input
    if ( argc == 1 )
    {
        cout << "NetworkAgent <name> <ip> <reporting server> <log location>" << endl;
        return( 1 );
    }
    else if ( ( argc == 2 && strcmp(argv[1], "help") == 0 ) || argc < 5 )
    {
        cout
        << "\nNetworkAgent Help\n"
        << "----------------------------------------------------------\n"
        << "NetworkAgent <name> <ip> <reporting server> <log location>\n"
        << endl;
        return( 2 );
    }


    // let's do some setup
    name = argv[1];
    ip = argv[2];
    reportingServer = argv[3];
    logPath = argv[4];

    // get our logging object here
    Logger logger( "Daemon  ", logPath );

    logger.log( "Starting the NetworkAgent" );
    
    // check for a log path
    if ( logPath.empty() )
    {
        logPath = "/var/log/NetworkHealthMonitorAgent.log"; 
    }

    // make our new agent
    cout << "\nAgent Details\n"
    << "-------------------------\n"
    << "Name: " << name << "\n"
    << "IP: " << ip << "\n"
    << "Reporting server: " << reportingServer << "\n"
    << "Log path: " << logPath << "\n" << endl;
    MonitoringAgent agent( name, ip, reportingServer, logPath );
    logger.log( "Now monitoring: " + name + " @ " + ip );
    logger.log( "Reporting to  : " + reportingServer );

    // terminate loop and close program if signal is received
    signal( SIGINT, signalWatcher );

    // Let's run the WatchDog until a kill signal is received!
    //for ( int i = 0; i < 5; i++ )
    while( 1 )
    {
        logger.log( "Running agent checks..." );
        agent.checkConnectivity();
        agent.checkLatency();
        agent.checkBandwidth();
        agent.checkCPU();
        sleep(60);
    }

    return 0;
}
