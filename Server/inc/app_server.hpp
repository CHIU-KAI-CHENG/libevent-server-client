#ifndef APP_SERVER_H
#define APP_SERVER_H
#define DELIMITER "|"

#include "server.hpp"

namespace server
{
   
    class App_Server : public Server
    {
    protected :

        static void do_accept(evutil_socket_t fd, short event, void * arg);
        static void error_cb(struct bufferevent * bev, short error, void * arg);
        static void read_cb(struct bufferevent * bev, void *arg); 
    public :

        static vector<Client*> clients;
        App_Server(int port, MySQLHandler * handler);
        void Accept();
        void Write(const char * msg);
    };

}






#endif /* APP_SERVER_H */