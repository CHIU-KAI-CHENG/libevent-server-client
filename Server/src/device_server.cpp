#include "device_server.hpp"
#include "app_server.hpp"
using namespace server;

/* device server */
Device_Server::Device_Server(int port) : Server(port)
{

}

vector<Client*> Device_Server::clients;

void Device_Server::Accept()
{
    clients.reserve(300000);
    base = event_base_new();
    listen_event = event_new(base, serverfd, EV_READ|EV_PERSIST, do_accept, (void*) base);
    event_add(listen_event, NULL);
    event_base_dispatch(base);
}

void Device_Server::do_accept(evutil_socket_t fd, short event, void * arg)
{
    struct event_base *base = (struct event_base *) arg;
    evutil_socket_t clientfd;
    struct sockaddr_in clientAddress;
    socklen_t slen = sizeof(clientAddress);

    clientfd = accept(fd, (struct sockaddr * ) &clientAddress, &slen);
    if (clientfd < 0)
    {
        cerr << "accept error";
        exit(1);
    }

    Client * client = new Client(clientfd, clientAddress);
    clients.push_back(client);
    client -> setIndex(clients.size() - 1);

    string clientIP = inet_ntoa(clientAddress.sin_addr);
    cout << "clientfd : " << clientfd << " accpet connection from " << clientIP << endl;


    struct bufferevent *bev = bufferevent_socket_new(base, clientfd, BEV_OPT_CLOSE_ON_FREE);
    client -> set_bev(bev);

    bufferevent_setcb(client -> get_bev(), read_cb, NULL, error_cb, client);
    bufferevent_enable(client -> get_bev(), EV_READ|EV_WRITE|EV_PERSIST);
}

void Device_Server::error_cb(struct bufferevent * bev, short error, void * arg)
{
    Client * client = (Client *) arg;
    if (error & BEV_EVENT_EOF)
    {
        cout << "connection closed from " << inet_ntoa(client -> getClientAddress().sin_addr);
        clients.erase(clients.begin() + client -> getIndex());
        cout << ", vector size : " << clients.size() << endl;
    }
    bufferevent_free(bev);
}

void Device_Server::read_cb(struct bufferevent * bev, void *arg)
{
    Client * client = (Client *) arg;
    int nbyte;
    char message[256];


    if(nbyte = bufferevent_read(bev, message, 256), nbyte > 0)
    {
        message[nbyte] = '\n';
        message[nbyte + 1] = '\0';
        unsigned i;
        for (i = 0; i < App_Server::clients.size(); i++)
        {
            cout << "msg from " << inet_ntoa(client -> getClientAddress().sin_addr) << " : " << message << endl;
            bufferevent_write((App_Server::clients[i] -> get_bev()), message, strlen(message));
        }
    }
}
