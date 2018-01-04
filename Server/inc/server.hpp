#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <vector>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <event2/event.h>
#include <event2/buffer.h>
#include <event2/bufferevent.h>
#include <event2/util.h>
#include <time.h>
using namespace std;

namespace server
{
    //client object in server
    class Client
    {
    protected:
        evutil_socket_t clientfd;
        struct sockaddr_in clientAddress;
        int index;
        struct bufferevent * bev;
    public:
        Client(evutil_socket_t fd, struct sockaddr_in sockaddr);
        ~Client();

        evutil_socket_t * getClientfd();
        struct sockaddr_in getClientAddress();

        void setIndex(int i);
        int getIndex();

        void set_bev(struct bufferevent * buf_ev);
        struct bufferevent * get_bev();
    };

    
    class Server
    {
    protected :

        evutil_socket_t serverfd;
        
        struct sockaddr_in serverAddress;

        struct event_base *base;
        struct event *listen_event;


    public :

        Server(int port);
        ~Server();
        void Start();
        virtual void Accept() = 0;

    };

    

}



#endif /* SERVER_H */