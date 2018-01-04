#include "mysqlhandler.hpp"

MySQLHandler::MySQLHandler(const char * host, const char * user, const char * password, const char * dbname, unsigned int port, const char * unix_socket, unsigned long client_flag)
{

    conn = mysql_init(NULL);
    
    if (!(mysql_real_connect(conn, host, user, password, dbname, port, unix_socket, client_flag)))
    {
        cerr << "Error : " << mysql_error(conn) << "[" << mysql_errno(conn) << "]" << endl;
        exit(1);
    }

    cout << "connection success" << endl;
}


