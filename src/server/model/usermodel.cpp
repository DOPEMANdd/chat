#include "usermodel.hpp"
#include "db.h"
#include <iostream>
using namespace std;

// user表的增加方法
bool UserModel::insert(User &user)
{
    // 组装sql语句
    char sql[1024] = {0};
    sprintf(sql, "insert into user(name, password, state) values('%s','%s','%s')",
            user.getName().c_str(), user.getPwd().c_str(), user.getState().c_str());

    MySQL mysql;
    if (mysql.connect())
    {
        if (mysql.update(sql))
        {
            // 获取插入用户成功的用户数据生成主键id
            user.setId(mysql_insert_id(mysql.getConnection()));
            return true;
        }
    }

    return false;
}

// 根据用户id查询用户信息
User UserModel::query(int id)
{
    // 组装sql语句
    char sql[1024] = {0};
    sprintf(sql, "select * from user where id = %d", id);

    MySQL mysql;
    if (mysql.connect())
    {
        MYSQL_RES *res = mysql.query(sql);
        if (res != nullptr)
        {
            MYSQL_ROW row = mysql_fetch_row(res); // return data as array of strings, 获取一行
            if (row != nullptr)
            {
                User user;
                user.setId(atoi(row[0])); // string to integer
                user.setName(row[1]);
                user.setPwd(row[2]);
                user.setState(row[3]);

                mysql_free_result(res); // 释放资源。避免内存泄露
                return user;
            }
        }
    }

    return User();
}

// 更新用户的状态信息
bool UserModel::updateState(User user)
{
    // 组装sql语句
    char sql[1024] = {0};
    sprintf(sql, "update user set state = '%s' where id = %d", user.getState().c_str(), user.getId());

    MySQL mysql;
    if (mysql.connect())
    {
        if (mysql.update(sql))
        {
            return true;
        }
    }

    return false;
}

void UserModel::resetState()
{
    // 组装sql语句
    char sql[1024] = {0};
    sprintf(sql, "update user set state = 'offline' where state = 'online'");

    MySQL mysql;
    if (mysql.connect())
    {
        mysql.update(sql);
    }
}
//{"msgid":1,"id":22,"password":"111111"}
//{"msgid":1,"id":15,"password":"666666"}
//{"msgid":5,"id":22,"from":"zhang di","to":15,"msg":"hello2"}
//{"msgid":6,"id":22,"friendid":13}
