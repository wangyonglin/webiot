#include <mysql/mysql.h>
typedef struct my_mysql
{
    MYSQL *mysql;
    const char *host;
    const char *user;
    const char *passwd;
    const char *db;
    unsigned int port;
    const char *unix_socket;
    unsigned long clientflag;
} my_mysql_t;

void obj_mysql_connect()
{
    mysql_real_connect();
}