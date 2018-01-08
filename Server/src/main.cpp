#include <iostream>
#include <thread>
#include "app_server.hpp"
#include "device_server.hpp"
#include "mysqlhandler.hpp"
#include "trash_can.hpp"
using namespace std;
using namespace server;

void app_server(App_Server * app_sv);
void device_server(Device_Server * dv_sv);


int main()
{
	printf("%f", a);
	MySQLHandler * dbHandler = new MySQLHandler("localhost", "root", "root", "trashcan", 3306, NULL, 0);
	dbHandler -> GetData("select * from location");

	App_Server app_listener(5200, dbHandler);
	Device_Server device_listener(5201, dbHandler);

	thread app_thread(app_server, &app_listener);
	thread device_thread(device_server, &device_listener);

	

	app_thread.join();
	device_thread.join();


	return 0;
}

void app_server(App_Server * app_sv)
{
	app_sv -> Start();
	app_sv -> Accept();
}

void device_server(Device_Server * dv_sv)
{
	dv_sv -> Start();
	dv_sv -> Accept();
}
