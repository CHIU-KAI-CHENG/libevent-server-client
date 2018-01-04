# Event-driven C++ server
## Description
I'm making a server project to handle the data transmission between embedded devices and user apps. The platform is going to be Ubuntu 16 LTS.

The ./inc/server.hpp includes the server class encapsulated with the event-driven machanism. The ./inc/device_server.hpp and ./inc/app_server.hpp respectively inherit the server class.

The ./src/main.cpp demonstrates the usage of both app-server and device-server, each of them running in a single thread to concurrently processing the requests from users and devices.

## Prerequisite
Should install the libevent2 library :

'sudo apt-get install libevent-dev'


## Excecution
Change to the directory same as the Makefile.

To build the project, just type 'make'.

To run the project, type 'make run'.