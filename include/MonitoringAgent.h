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
    string  reportingServer;
    string  logPath;
    
    // CONSTRUCTORS
    MonitoringAgent( string assignedName, string assignedIP, string assignedReportingServer, string assignedLogPath );

    // METHODS
    int     checkConnectivity();
    void    checkBandwidth();
    void    checkLatency();
    void    checkCPU();

private:

    // METHODS
    void    report( string server );

};

#endif
