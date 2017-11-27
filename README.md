# NetworkAgent

### About
NetworkAgent is a kind of daemon that monitors a host and reports back to a central server.

### Syntax
    NetworkAgent <name> <ip address> <reporting server>
    NetworkAgent -c </path/to/config>

### Methods

##### MonitoringAgent
_checkConnectivity_
Checks the connectivity of the host to the web.

_checkLatency_
Checks the network latency of the host.

_checkBandwidth_
Checks the current bandwidth limits of the host.

_checkCPU_
Checks the CPU status of the host.
Note: Not currently functional.

##### Logger
_log_
Takes any message passed to it and logs the message to a specified file.

##### Reporter
_report_
Reports any information gathered by the agent to the specified server.
The reporter uses encryption to protect any data passed to the central server.
