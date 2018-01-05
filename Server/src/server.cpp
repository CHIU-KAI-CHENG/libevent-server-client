#include "server.hpp"
using namespace server;

/* server */

Server::Server(int port)
{
    serverfd = socket(PF_INET, SOCK_STREAM, 0);
    if (serverfd < 0)
    {
        cerr << "socket opening error";
        exit(1);
    }
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddress.sin_port = htons(port);
    if (bind(serverfd, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0)
    {
        cerr << "binding failed";
        exit(1);
    }    
}

Server::~Server()
{
    event_free(listen_event);
    event_base_free(base);
}


void Server::Start()
{
    if (listen(serverfd, SOMAXCONN) < 0)
    {
        cerr << "listening failed";
        exit(1);
    }
    cout << "listening for " << SOMAXCONN << endl;

    evutil_make_socket_nonblocking(serverfd);
}



/* client in server*/
Client::Client(evutil_socket_t fd, struct sockaddr_in sockaddr)
{
    clientfd = fd;
    clientAddress = sockaddr;
}

Client::~Client()
{
    close(clientfd);
}

evutil_socket_t * Client::getClientfd()
{
    return &clientfd;
}

struct sockaddr_in Client::getClientAddress()
{
    return clientAddress;
}

void Client::setIndex(int i)
{
    index = i;
}

int Client::getIndex()
{
    return index;
}

void Client::set_bev(struct bufferevent * buf_ev)
{
    bev = buf_ev;
}

struct bufferevent * Client::get_bev()
{
    return bev;
}