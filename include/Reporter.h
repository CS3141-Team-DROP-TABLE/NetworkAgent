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
    void report( int type, int status );

private:

};

#endif
