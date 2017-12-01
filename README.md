# NetworkAgent

### About
NetworkAgent is a kind of daemon that monitors a host and reports back to a central server.
To create a new agent go to <a href="https://tsp.bilderback.me" target="_blank">tsp.bilderback.me</a> and add an agent to your account. Once a new agent is added to your account you will use the ID that is given to you when running the agent. See the Syntax below for more on how to run the agent. Once running the NetworkAgent will monitor the status of the host and report information back to the central server to update the status on the website, allowing you to monitor your host alongside your other monitored servers.

### Syntax
    NetworkAgent <Agent ID> <ip> <reporting server> <server domain> <certificate path>
    NetworkAgent -c </path/to/config>

    Agent ID: The ID given to you by the web app for your agent to report updates with.
    IP: IP address of the agent.
    Reporting Server: The server that the agent will be reporting updates to.
    Server Domain: Used for encryption, this is the domain of the certificate used for encryption.
    Certificate Path: The path to the certificate used for encryption.

### Methods

##### MonitoringAgent
_checkConnectivity_
Checks the connectivity of the host to the web.
The connectivity checker uses cURL to check if a connection can be made to a website. If the connection is made successfully, then the host has a connection.

_checkBandwidth_
Checks the current bandwidth limits of the host.
The agent checks the bandwidth of the host by downloading a 100M file from our central server. This is a large enough file to get a rough estimate of the current download speeds of the host.

##### Logger
_log_
Takes any message passed to it and logs the message to a specified file.
The logger will log to /var/log/NetworkAgent.log on *NIX type machines, and to C:\Program Files(x86)\NetworkAgent\log\NetworkAgent.log on Windows based machines.

##### Reporter
_report_
Reports any information gathered by the agent to the specified server.
The reporter uses encryption to protect any data passed to the central server.
