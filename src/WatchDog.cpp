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
//#include "configLoader.h"
//#include "AVL.h"

using namespace std;

// variables to set later on
string id;
string aid;
string ip;
string reportingServer;
string configPath;
string domain;
string certPath;

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
        cout << "\nUsage: \n"
            << "NetworkAgent <Agent ID> <ip> <reporting server> <server domain> <certificate path>\n"
            << "NetworkAgent -c <path to configuration file>\n"
            << "NetworkAgent help\n"
            << endl;
        return( 1 );
    }
    else if ( ( argc == 3 && strcmp(argv[1], "-c") == 0 ) )
    {
        // read in config file
        //configPath = argv[2];

        /*
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
        */

        /*
        struct config conf;
        config_loader_init(&conf, 0, 0);
        load_config(&conf, argv[2]);

        id = get_config(&conf, "id");
        aid = "A" + id + ";";
        ip = get_config(&conf, "ip");
        reportingServer = get_config(&conf, "server");
        domain = get_config(&conf, "domain");
        certPath = get_config(&conf, "certificate");
        */

    }
    else if ( ( argc == 2 && strcmp(argv[1], "help") == 0 ) || argc < 6 )
    {
        // display help
        cout
        << "\nNetworkAgent Help\n"
        << "----------------------------------------------------------\n"
        << "NetworkAgent <Agent ID> <reporting server> <server domain> <certificate path>\n"
        << "NetworkAgent -c /path/to/file\n\n"
        << "Agent ID: The ID given to you by the web app for your agent to report updates with.\n"
        << "Reporting Server: The server that the agent will be reporting updates to.\n"
        << "Server Domain: Used for encryption, this is the domain of the certificate used for encryption.\n"
        << "Certificate Path: The path to the certificate used for encryption.\n"
        << endl;
        return( 2 );
    }
    else
    {
        // read in settings from input
        id = argv[1];
        aid = "A" + id + ";";
        ip = argv[2];
        reportingServer = argv[3];
        domain = argv[4];
        certPath = argv[5];
    }

    daemonLogger.log( "Starting the NetworkAgent" );

    // make our new agent
    cout << "\nAgent Details\n"
    << "-------------------------\n"
    << "Agent ID: " << aid << "\n"
    << "Reporting server: " << reportingServer << "\n" << endl;
    MonitoringAgent agent( aid );
    daemonLogger.log( "Now monitoring: " + aid );
    daemonLogger.log( "Reporting to  : " + reportingServer );

    // terminate loop and close program if signal is received
    signal( SIGINT, signalWatcher );

    // reporter for reporting check statuses to
    Reporter reporter( reportingServer, domain, certPath );

    // Let's run the WatchDog until a kill signal is received!
    //for ( int i = 0; i < 5; i++ )
    while( 1 )
    {
        daemonLogger.log( "Running agent checks..." );
        reporter.report( aid, 0, agent.checkIP() );
        reporter.report( aid, 1, agent.checkConnectivity() );
        //reporter.report( aid, 2, agent.checkLatency() );
        reporter.report( aid, 3, agent.checkBandwidth() );
        //reporter.report( aid, 4, agent.checkCPU() );
        sleep(60);
    }

    // clean up
    reporter.deinit();

    return 0;
}
