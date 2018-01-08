#include "app_server.hpp"
using namespace server;

/* app_server */
App_Server::App_Server(int port, MySQLHandler * handler) : Server(port, handler)
{

}

vector<Client*> App_Server::clients;

void App_Server::Accept()
{
    clients.reserve(300000);
    base = event_base_new();
    listen_event = event_new(base, serverfd, EV_READ|EV_PERSIST, do_accept, (void*) base);
    event_add(listen_event, NULL);
    event_base_dispatch(base);
}

void App_Server::do_accept(evutil_socket_t fd, short event, void * arg)
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
    cout << "clientfd : " << clientfd << " accpet connection from " << clientIP << ", fd = " << clientfd << endl;

    client -> set_bev(bufferevent_socket_new(base, clientfd, BEV_OPT_CLOSE_ON_FREE));

    bufferevent_setcb(client -> get_bev(), read_cb, NULL, error_cb, client);
    bufferevent_enable(client -> get_bev(), EV_READ|EV_WRITE|EV_PERSIST);
}

void App_Server::error_cb(struct bufferevent * bev, short error, void * arg)
{
    Client * client = (Client *) arg;
    if (error & BEV_EVENT_EOF)
    {
        cout << "connection closed from " << inet_ntoa(client -> getClientAddress().sin_addr);
        clients.erase(clients.begin() + client -> getIndex());
        cout << ", vector size : " << clients.size() << endl;
        delete client;
    }
    bufferevent_free(bev);
}

void App_Server::read_cb(struct bufferevent * bev, void *arg)
{
    evutil_socket_t fd = bufferevent_getfd(bev);
    int nbyte;
    char message[256];

    if (nbyte = bufferevent_read(bev, message, 256), nbyte > 0)
    {
        message[nbyte] = '\0';
        cout << "fd " << fd << " message : " << message << nbyte << " bytes" << endl;
    }
}

void App_Server::Write(const char * msg)
{
    unsigned i;
    for (i = 0; i < clients.size(); i++)
    {
        cout << msg << endl;
        bufferevent_write(clients[i] -> get_bev(), msg, strlen(msg));
    }
}

