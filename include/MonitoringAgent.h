// Header file for Monitoring Agent

#ifndef MONITORINGAGENT_H
#define MONITORINGAGENT_H

using namespace std;

class MonitoringAgent
{

public:

    // VARIABLES
    string  name;
    string  ip;
    
    // CONSTRUCTORS
    MonitoringAgent( string assignedName, string assignedIP );

    // METHODS
    string  checkConnectivity();
    string  checkBandwidth();
    string  checkLatency();
    string  checkCPU();

private:

};

#endif
