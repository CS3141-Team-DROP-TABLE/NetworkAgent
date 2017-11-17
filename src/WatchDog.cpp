// Team Software Project Fall 2017
// Team "; DROP TABLE team_names;
// Watch Dog: uses the Monitoring Agent to constantly check the host it's running on.

// C libraries
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstring>
#include <csignal>
#include <unistd.h>

// headers
#include "MonitoringAgent.h"
#include "Logger.h"
#include "Reporter.h"

using namespace std;

// variables to set later on
string name;
string ip;
string reportingServer;
string configPath;

// logger for making logs
Logger daemonLogger( "Daemon  " );

// method to watch for signals
void signalWatcher( int signum )
{
    cout << "\n\nSignal received, exiting WatchDog..." << endl;
    daemonLogger.log( "Signal received, exiting WatchDog..." );
    exit( signum );
}

int main( int argc, char* argv[] ) 
{
    // read in the input
    if ( argc == 1 )
    {
        // no input
        cout << "Usage: \n"
            << "NetworkAgent [-v] <name> <ip> <reporting server>"
            << "NetworkAgent [-v] -c <path to configuration file>"
            << endl;
        return( 1 );
    }
    else if ( ( argc == 3 && strcmp(argv[1], "-c") == 0 ) )
    {
        // read in config file
        configPath = argv[2];
        ifstream configFile;
        configFile.open(configPath, ios_base::in);
        if ( !configFile )
        {
            cout << "Unable to open " << configPath << endl;
            exit( 4 );
        }

        // read through and set settings
        while ( configFile.get() )
        {
            
        }

        configFile.close();
    }
    else if ( ( argc == 2 && strcmp(argv[1], "help") == 0 ) || argc < 4 )
    {
        // display help
        cout
        << "\nNetworkAgent Help\n"
        << "----------------------------------------------------------\n"
        << "NetworkAgent <name> <ip> <reporting server>\n"
        << endl;
        return( 2 );
    }
    else
    {
        // read in settings from input
        name = argv[1];
        ip = argv[2];
        reportingServer = argv[3];
    }

    daemonLogger.log( "Starting the NetworkAgent" );

    // make our new agent
    cout << "\nAgent Details\n"
    << "-------------------------\n"
    << "Name: " << name << "\n"
    << "IP: " << ip << "\n"
    << "Reporting server: " << reportingServer << "\n" << endl;
    MonitoringAgent agent( name, ip );
    daemonLogger.log( "Now monitoring: " + name + " @ " + ip );
    daemonLogger.log( "Reporting to  : " + reportingServer );

    // terminate loop and close program if signal is received
    signal( SIGINT, signalWatcher );

    // reporter for reporting check statuses to
    Reporter reporter( reportingServer, "nhs_server_domain.com", "/Users/bbilder/Git/NetworkAgent/cert/intermediate.cert.pem" );

    // Let's run the WatchDog until a kill signal is received!
    //for ( int i = 0; i < 5; i++ )
    while( 1 )
    {
        daemonLogger.log( "Running agent checks..." );
        reporter.report( 1, agent.checkConnectivity() );
        reporter.report( 2, agent.checkLatency() );
        reporter.report( 3, agent.checkBandwidth() );
        reporter.report( 4, agent.checkCPU() );
        sleep(60);
    }

    // clean up
    reporter.deinit();

    return 0;
}
