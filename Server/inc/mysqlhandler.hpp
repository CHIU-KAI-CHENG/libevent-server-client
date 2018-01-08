#ifndef MYSQL_HANDLER_H
#define MYSQL_HANDLER_H

#define LAT 3
#define LNG 4

#include <iostream>
#include <vector>
#include <mysql/mysql.h>
#include "mysqlhandler.hpp"
#include "trash_can.hpp"


using namespace std;


class MySQLHandler
{
private:
    MYSQL * conn;
    MYSQL_RES * res;
    MYSQL_ROW row;
    int cols;
    vector<TrashCan*> trashcans;
    


public:
    MySQLHandler(const char * host, const char * user, const char * password, const char * dbname, unsigned int port, const char * unix_socket, unsigned long client_flag);
    void GetData(const char * sql);
    vector<TrashCan*> GetTrashCans();
};



#endif /* MYSQL_HANDLER_H */