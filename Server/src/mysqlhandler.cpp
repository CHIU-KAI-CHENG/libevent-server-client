#include "mysqlhandler.hpp"

MySQLHandler::MySQLHandler(const char * host, const char * user, const char * password, const char * dbname, unsigned int port, const char * unix_socket, unsigned long client_flag)
{

    conn = mysql_init(NULL);
    
    if (!(mysql_real_connect(conn, host, user, password, dbname, port, unix_socket, client_flag)))
    {
        cerr << "Error : " << mysql_error(conn) << "[" << mysql_errno(conn) << "]" << endl;
        exit(1);
    }
    mysql_set_character_set(conn, "utf8");

    cout << "connection success" << endl;
}

void MySQLHandler::GetData(const char * sql)
{
    mysql_query(conn, sql);
    res = mysql_store_result(conn);
    cols = mysql_num_fields(res);
    while (row = mysql_fetch_row(res))
    {
        TrashCan * trashcan = new TrashCan(row[0], row[1], row[2], atof(row[3]), atof(row[4]));
        trashcans.push_back(trashcan);
        printf("%f\n", trashcan -> latitude);
    }
}

vector<TrashCan*> MySQLHandler::GetTrashCans()
{
    return trashcans;
}

