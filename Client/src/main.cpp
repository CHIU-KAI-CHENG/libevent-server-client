#include "client.hpp"
#include "PWM.hpp"

void read_cb(bufferevent *bev, void * arg);


int main()
{   

    Client client(5201, "192.168.1.6", read_cb);
    client.Connect();

 
    return 0;
}

void read_cb(bufferevent *bev, void * arg)
{

}