#ifndef DEVICE_SERVER_H
#define DEVICE_SERVER_H

#include "server.hpp"
namespace server
{
    class Device_Server : public Server
    {
    protected:

        static void do_accept(evutil_socket_t fd, short event, void * arg);
        static void error_cb(struct bufferevent * bev, short error, void * arg);
        static void read_cb(struct bufferevent * bev, void *arg); 
    public:

        static vector<Client*> clients;
        Device_Server(int port, MySQLHandler * handler);
        void Accept();

    };
}




#endif /* DEVICE_SERVER_H */