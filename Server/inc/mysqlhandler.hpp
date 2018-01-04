#ifndef MYSQL_HANDLER_H
#define MYSQL_HANDLER_H

#include <iostream>
#include <mysql/mysql.h>


using namespace std;


class MySQLHandler
{
private:
    MYSQL * conn;

public:
    MySQLHandler(const char * host, const char * user, const char * password, const char * dbname, unsigned int port, const char * unix_socket, unsigned long client_flag);
    
};



#endif /* MYSQL_HANDLER_H */