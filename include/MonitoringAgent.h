// Header file for Monitoring Agent

#ifndef MONITORINGAGENT_H
#define MONITORINGAGENT_H

using namespace std;

class MonitoringAgent
{

public:

    // VARIABLES
    string  name;
    
    // CONSTRUCTORS
    MonitoringAgent( string assignedName );

    // METHODS
    string  checkIP();
    string  checkConnectivity();
    string  checkBandwidth();
    string  checkLatency();
    string  checkCPU();

private:

};

#endif
