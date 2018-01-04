#ifndef APP_SERVER_H
#define APP_SERVER_H

#include "server.hpp"

namespace server
{
    class App_Client : public Client
    {
    protected :
        struct event * periodic_event;
    public :
        App_Client(evutil_socket_t fd, struct sockaddr_in sockaddr);

        void set_periodic_event(struct event* ev);
        struct event * get_periodic_event();
    };


    class App_Server : public Server
    {
    protected :
        static vector<App_Client> clients;

        static void do_accept(evutil_socket_t fd, short event, void * arg);
        static void error_cb(struct bufferevent * bev, short error, void * arg);
        static void read_cb(struct bufferevent * bev, void *arg); 
        static void periodic_send(int fd, short event, void * arg);
    public :
        App_Server(int port);
        void Accept();
    };

}






#endif /* APP_SERVER_H */