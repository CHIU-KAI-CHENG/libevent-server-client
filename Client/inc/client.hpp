#ifndef CLIENT_H
#define CLIENT_H

#include <event2/event.h>
#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <event2/util.h>

#include <iostream>
#include <string>
#include <string.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;

class Client
{
private:
    evutil_socket_t clientfd;
    struct sockaddr_in serverAddress;
    struct event_base *base;
    struct bufferevent * bev;
    static void event_cb(struct bufferevent * buf_ev, short event, void *arg);
    bufferevent_data_cb read_cb;

public:
    Client(int port, const char * ip_addr, bufferevent_data_cb read_ev);
    void Connect();
    void Write(char * msg);
    evutil_socket_t GetClientfd();
};




#endif /* CLIENT_H */