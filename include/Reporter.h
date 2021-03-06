// Header file for reporter

using namespace std;

#ifndef REPORTER_H
#define REPORTER_H

class Reporter
{
public:

    // VARIABLES
    string hostname;
    string trustedName;
    string CAFilePath;

    // CONSTRUCTORS
    Reporter( string server, string name, string path );

    // METHODS
    void report( string id, int type, string status );
    void deinit();

private:

    void connect();
    void disconnect();

};

#endif
