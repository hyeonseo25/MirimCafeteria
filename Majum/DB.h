#pragma once
#include <mysql.h>
#ifndef DB_H
#define DB_H
    MYSQL Conn;             // MySQL ������ ���� ����ü
    MYSQL* ConnPtr = NULL;  // MySQL �ڵ�
    MYSQL_RES* Result;      // ���������� ����� ��� ����ü ������
    MYSQL_ROW Row;          // ���������� ����� ���� ���� ������ ��� ����ü
    int Stat;               // ������û �� ���(����, ����)
#endif