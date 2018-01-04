#include "client.hpp"

Client::Client(int port, const char * ip_addr, bufferevent_data_cb read_ev)
{
    clientfd = socket(PF_INET, SOCK_STREAM, 0);
    if (clientfd < 0)
    {
        cerr << "socket opening error";
        exit(1);
    }
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    if (!inet_aton(ip_addr, &serverAddress.sin_addr))
    {
        cerr << "ip converting error";
        exit(1);
    }
    read_cb = read_ev;

}

void Client::Connect()
{
    if (connect(clientfd, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0)
    {
        cerr << "cannot connect to the server";
        exit(1);
    }
    evutil_make_socket_nonblocking(clientfd);
    base = event_base_new();
    bev = bufferevent_socket_new(base, clientfd, BEV_OPT_CLOSE_ON_FREE);
    bufferevent_setcb(bev, read_cb, NULL, NULL, NULL);
    bufferevent_enable(bev, EV_READ | EV_PERSIST);

    event_base_dispatch(base);
}

evutil_socket_t Client::GetClientfd()
{
    return clientfd;
}



