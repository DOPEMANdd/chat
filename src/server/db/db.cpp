#include "db.h"
#include <muduo/base/Logging.h>

// 初始化数据库连接
MySQL::MySQL()
{
    _conn = mysql_init(nullptr);
}

// 释放数据库连接资源
MySQL::~MySQL()
{
    if (_conn != nullptr)
        mysql_close(_conn);
}

// 连接数据库
bool MySQL::connect()
{
    MYSQL *p = mysql_real_connect(_conn, server.c_str(), user.c_str(),
                                  password.c_str(), dbname.c_str(), 3306, nullptr, 0);
    if (p != nullptr)
    {
        // c/c++默认的编码字符是ASCII，如果不设置，从MySQL上拉下来的中文显示乱码
        mysql_query(_conn, "set names gbk");
        LOG_INFO << "connect mysql success!";
    }
    else
    {
        LOG_INFO << "connect mysql fail!";
    }
    return p;
}

// 更新操作
bool MySQL::update(string sql)
{
    if (mysql_query(_conn, sql.c_str()))
    {
        LOG_INFO << __FILE__ << ":" << __LINE__ << ":"
                 << sql << "更新失败!";
        return false;
    }
    return true;
}

// 查询操作
MYSQL_RES *MySQL::query(string sql)
{
    if (mysql_query(_conn, sql.c_str())) // mysql_query函数执行成功返回0
    {
        LOG_INFO << __FILE__ << ":" << __LINE__ << ":" // 宏定义__file__当前源文件名，__line__当前程序的行号
                 << sql << "查询失败!";
        return nullptr;
    }
    return mysql_use_result(_conn);
}

// 获取当前的连接
MYSQL *MySQL::getConnection()
{
    return _conn;
}