#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <string>
#include <mysql.h>
#include <conio.h>
#include "DB.h" 

#pragma comment(lib, "libmySQL.lib")

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define SUBMIT 4

using namespace std;

void PrintLoading(string);
void gotoxy(int, int);
int keyControl();
void connectDB();
void setCursor(boolean);

class DataBase {
private:

public:
    int totalProductNum = 0;
    string productName = "";
    DataBase() {
        this->totalProductNum = 0;
        productName = "";
    }
    ~DataBase() {

    }
    void getinfo() {
        this->totalProductNum = 0;
        char* Query = "SELECT * FROM product";      // �����ݷ��� �����ϰ� ������ �ۼ�
        Stat = mysql_query(ConnPtr, Query);         // ���� ��û �� �������� �޾ƿ���
        if (Stat != 0)
        {
            cout << stderr << "error : " << mysql_error(&Conn);
        }
        else {
            Result = mysql_store_result(ConnPtr);           // ��� Ȯ���ϱ�
            while ((Row = mysql_fetch_row(Result)) != NULL) // ��� ����ϱ�
            {
                totalProductNum++; // DB�� �� ��ǰ������ �� �� ����
                if ((((string)Row[0]).length()) / 2 <= 2) {
                    printf("   %s\t\t\t%s\t\t%s\n", Row[0], Row[1], Row[2]);
                }
                else if ((((string)Row[0]).length()) / 2 <= 6) {
                    printf("   %s\t\t%s\t\t%s\n", Row[0], Row[1], Row[2]);
                }
                else {
                    printf("   %s\t%s\t\t%s\n", Row[0], Row[1], Row[2]);
                }

            }
            mysql_free_result(Result);                      // ��� ����
        }
    }
    void getinfo(string name) {
        string Query = "";     // �����ݷ��� �����ϰ� ������ �ۼ�
        Query += "SELECT * FROM product where name = '";
        Query += name;
        Query += "'";
        Stat = mysql_query(ConnPtr, Query.c_str());         // ���� ��û �� �������� �޾ƿ���
        if (Stat != 0)
        {
            cout << stderr << "error : " << mysql_error(&Conn);
        }
        else {
            Result = mysql_store_result(ConnPtr);           // ��� Ȯ���ϱ�
            while ((Row = mysql_fetch_row(Result)) != NULL) // ��� ����ϱ�
            {
                printf("%s %s�� %s��", Row[0], Row[1], Row[2]);
            }
            mysql_free_result(Result);                      // ��� ����
        }
    }
    void getinfoName(int num) {
        getProductName(num);
        string Query = "";     // �����ݷ��� �����ϰ� ������ �ۼ�
        Query += "SELECT * FROM product where name = '";
        Query += this->productName;
        Query += "'";
        Stat = mysql_query(ConnPtr, Query.c_str());         // ���� ��û �� �������� �޾ƿ���
        if (Stat != 0)
        {
            cout << stderr << "error : " << mysql_error(&Conn);
        }
        else {
            Result = mysql_store_result(ConnPtr);           // ��� Ȯ���ϱ�
            while ((Row = mysql_fetch_row(Result)) != NULL) // ��� ����ϱ�
            {
                if ((((string)Row[0]).length()) / 2 <= 2) {
                    printf("   %s\t\t\t", Row[0]);
                }
                else if ((((string)Row[0]).length()) / 2 <= 6) {
                    printf("   %s\t\t", Row[0]);
                }
                else {
                    printf("   %s\t", Row[0]);
                }
            }
            mysql_free_result(Result);                      // ��� ����
        }
    }
    int getinfo(string name, int num) {
        string Query = "";     // �����ݷ��� �����ϰ� ������ �ۼ�
        Query += "SELECT * FROM product where name = '";
        Query += name;
        Query += "'";
        Stat = mysql_query(ConnPtr, Query.c_str());         // ���� ��û �� �������� �޾ƿ���
        if (Stat != 0)
        {
            cout << stderr << "error : " << mysql_error(&Conn);
        }
        else {
            Result = mysql_store_result(ConnPtr);           // ��� Ȯ���ϱ�
            while ((Row = mysql_fetch_row(Result)) != NULL) // ��� ����ϱ�
            {
                if (num == 2) {
                    return atoi(Row[1]);
                }
                else if (num == 3) {
                    return atoi(Row[2]);
                }
            }
            mysql_free_result(Result);                      // ��� ����
        }
    }
    void getrequestinfo() {
        this->totalProductNum = 0;
        char* Query = "SELECT * FROM request";      // �����ݷ��� �����ϰ� ������ �ۼ�
        Stat = mysql_query(ConnPtr, Query);         // ���� ��û �� �������� �޾ƿ���
        if (Stat != 0)
        {
            cout << stderr << "error : " << mysql_error(&Conn);
        }
        else {
            Result = mysql_store_result(ConnPtr);           // ��� Ȯ���ϱ�
            while ((Row = mysql_fetch_row(Result)) != NULL) // ��� ����ϱ�
            {
                if (atoi(Row[5]) != 1 && atoi(Row[5]) != 2) {
                    totalProductNum++; // DB�� �� ��ǰ������ �� �� ����
                    if ((((string)Row[3]).length()) / 2 <= 3) {
                        printf("   %s\t\t%s\t\t%s\t\t\t%s\n", Row[1], Row[2], Row[3], Row[4]);
                    }
                    else if ((((string)Row[3]).length()) / 2 <= 7) {
                        printf("   %s\t\t%s\t\t%s\t\t%s\n", Row[1], Row[2], Row[3], Row[4]);
                    }
                    else {
                        printf("   %s\t\t%s\t\t%s\t%s\n", Row[1], Row[2], Row[3], Row[4]);
                    }
                }
            }
            mysql_free_result(Result);                      // ��� ����
        }
    }
    void getrequestinfo_2() {
        this->totalProductNum = 0;
        char* Query = "SELECT * FROM request";      // �����ݷ��� �����ϰ� ������ �ۼ�
        Stat = mysql_query(ConnPtr, Query);         // ���� ��û �� �������� �޾ƿ���
        if (Stat != 0)
        {
            cout << stderr << "error : " << mysql_error(&Conn);
        }
        else {
            Result = mysql_store_result(ConnPtr);           // ��� Ȯ���ϱ�
            while ((Row = mysql_fetch_row(Result)) != NULL) // ��� ����ϱ�
            {
                if (atoi(Row[5]) == 1) {
                    totalProductNum++; // DB�� �� ��ǰ������ �� �� ����
                    if ((((string)Row[3]).length()) / 2 <= 3) {
                        printf("   %s\t\t%s\t\t%s\t\t\t%s\t\t���ε�\n", Row[1], Row[2], Row[3], Row[4]);
                    }
                    else if ((((string)Row[3]).length()) / 2 <= 7) {
                        printf("   %s\t\t%s\t\t%s\t\t%s\t\t���ε�\n", Row[1], Row[2], Row[3], Row[4]);
                    }
                    else {
                        printf("   %s\t\t%s\t\t%s\t%s\t\t���ε�\n", Row[1], Row[2], Row[3], Row[4]);
                    }
                }
                else if (atoi(Row[5]) == 2) {
                    totalProductNum++; // DB�� �� ��ǰ������ �� �� ����
                    if ((((string)Row[3]).length()) / 2 <= 3) {
                        printf("   %s\t\t%s\t\t%s\t\t\t%s\t\t������\n", Row[1], Row[2], Row[3], Row[4]);
                    }
                    else if ((((string)Row[3]).length()) / 2 <= 7) {
                        printf("   %s\t\t%s\t\t%s\t\t%s\t\t������\n", Row[1], Row[2], Row[3], Row[4]);
                    }
                    else {
                        printf("   %s\t\t%s\t\t%s\t%s\t\t������\n", Row[1], Row[2], Row[3], Row[4]);
                    }
                }
            }
            mysql_free_result(Result);                      // ��� ����
        }
    }
    void getProductName(int num) {
        int count = 1;
        char* Query = "SELECT * FROM product";      // �����ݷ��� �����ϰ� ������ �ۼ�
        Stat = mysql_query(ConnPtr, Query);         // ���� ��û �� �������� �޾ƿ���
        if (Stat != 0)
        {
            cout << stderr << "error : " << mysql_error(&Conn);
        }
        else {
            Result = mysql_store_result(ConnPtr);           // ��� Ȯ���ϱ�
            while ((Row = mysql_fetch_row(Result)) != NULL) // ��� ����ϱ�
            {
                if (count == num) {
                    this->productName = Row[0];
                    break;
                }
                count++;
            }
            mysql_free_result(Result);                      // ��� ����
        }
    }
    void dealrequest(int num, int deal) {
        int count = 1;
        string ownnum = "";
        char* Query = "SELECT * FROM request";      // �����ݷ��� �����ϰ� ������ �ۼ�
        Stat = mysql_query(ConnPtr, Query);         // ���� ��û �� �������� �޾ƿ���
        if (Stat != 0)
        {
            cout << stderr << "error : " << mysql_error(&Conn);
        }
        else {
            Result = mysql_store_result(ConnPtr);           // ��� Ȯ���ϱ�
            while ((Row = mysql_fetch_row(Result)) != NULL) // ��� ����ϱ�
            {
                if (atoi(Row[5]) != 1 && atoi(Row[5]) != 2) {
                    if (count == num) {
                        ownnum = (string)Row[0];
                        break;
                    }
                    count++;
                }
            }
            mysql_free_result(Result);                      // ��� ����
        }
        char temp[10];
        string Query2 = "";     // �����ݷ��� �����ϰ� ������ �ۼ�
        Query2 += "UPDATE request SET approval = ";
        _itoa(deal, temp, 10);
        Query2 += temp;
        Query2 += " WHERE serialNum = ";
        Query2 += ownnum;
        Stat = mysql_query(ConnPtr, Query2.c_str());         // ���� ��û �� �������� �޾ƿ���
        if (Stat != 0)
        {
            cout << stderr << "error : " << mysql_error(&Conn);
        }
    }

    int addProductDB(char* name = "productname", int price = 0, int inventory = 0) {
        char temp[10];
        string Query = "";     // �����ݷ��� �����ϰ� ������ �ۼ�
        Query += "insert into product(name,price,inventory) values ('";
        Query += name;
        Query += "',";
        _itoa(price, temp, 10);
        Query += temp;
        Query += ",";
        _itoa(inventory, temp, 10);
        Query += temp;
        Query += ")";
        Stat = mysql_query(ConnPtr, Query.c_str());         // ���� ��û �� �������� �޾ƿ���
        if (Stat != 0)
        {
            cout << stderr << "error : " << mysql_error(&Conn);
        }
        return 0;
    }
    int deleteDB(string name) {
        string Query = "";     // �����ݷ��� �����ϰ� ������ �ۼ�
        Query += "delete from product where name='";
        Query += name;
        Query += "'";
        Stat = mysql_query(ConnPtr, Query.c_str());         // ���� ��û �� �������� �޾ƿ���
        if (Stat != 0)
        {
            cout << stderr << "error : " << mysql_error(&Conn);
        }
        return 0;
    }
    int updateDB(string name, string new_name, int price, int inventory) {
        char temp[10];
        string Query = "";     // �����ݷ��� �����ϰ� ������ �ۼ�
        Query += "UPDATE product SET name = '";
        Query += new_name;
        Query += "', price = ";
        _itoa(price, temp, 10);
        Query += temp;
        Query += ", inventory = ";
        _itoa(inventory, temp, 10);
        Query += temp;
        Query += " WHERE name = '";
        Query += name;
        Query += "'";
        Stat = mysql_query(ConnPtr, Query.c_str());         // ���� ��û �� �������� �޾ƿ���
        if (Stat != 0)
        {
            cout << stderr << "error : " << mysql_error(&Conn);
        }
        return 0;
    }
    int updateDB(int num, int inventory) {
        getProductName(num);
        char temp[10];
        string Query = "";     // �����ݷ��� �����ϰ� ������ �ۼ�
        Query += "UPDATE product SET inventory = ";
        _itoa(inventory, temp, 10);
        Query += temp;
        Query += " WHERE name = '";
        Query += this->productName;
        Query += "'";
        Stat = mysql_query(ConnPtr, Query.c_str());         // ���� ��û �� �������� �޾ƿ���
        if (Stat != 0)
        {
            cout << stderr << "error : " << mysql_error(&Conn);
        }
        return 0;
    }
    int addRequestDB(int studentNum, string studentName, string productName, int productNum) {
        char temp[10];
        string Query = "";     // �����ݷ��� �����ϰ� ������ �ۼ�
        Query += "insert into request(studentNum, studentName, productName, productNum, approval) values (";
        _itoa(studentNum, temp, 10);
        Query += temp;
        Query += ",'";
        Query += studentName;
        Query += "', '";
        Query += productName;
        Query += "', ";
        _itoa(productNum, temp, 10);
        Query += temp;
        Query += ", 0)";
        Stat = mysql_query(ConnPtr, Query.c_str());         // ���� ��û �� �������� �޾ƿ���
        if (Stat != 0)
        {
            cout << stderr << "error : " << mysql_error(&Conn);
        }
        return 0;
    }
};
class Person {
public:
    string job;
};
class Manager : public Person { // ���
private:
    int password = 5588;
    int x;
    int y;
    int select;
    boolean selectfinish = false;
    DataBase db;
public:
    Manager() {
        job = "������";
        db = DataBase();
    }
    ~Manager() {

    }
    int checkPassword(int pw) {
        if (this->password != pw) {
            return -1;
        }
        return 0;
    }
    int manageProduct() {
        system("cls");
        x = 1;
        y = 6;
        gotoxy(52, 1);
        cout << "[�ڷΰ���]";
        gotoxy(0, 0);
        cout << "\n\n   ��ǰ��\t\t����\t\t���\n";
        cout << "\n  =====================================================================\n\n";
        db.getinfo();
        cout << "   [+��ǰ�߰�]";
    manageProduct:
        gotoxy(x, y);
        cout << ">";
        do {
            int n = keyControl();
            switch (n) {
            case UP: {
                if (y == 6) {
                    gotoxy(x, y);
                    cout << " ";
                    gotoxy(50, 1);
                    cout << ">";
                    y = 1;
                }
                if (y > 6) {
                    gotoxy(x, y);
                    cout << " ";
                    y -= 1;
                    gotoxy(x, y);
                    cout << ">";
                }
                break;
            }

            case DOWN: {
                if (y == 1) {
                    gotoxy(50, 1);
                    cout << " ";
                    y = 6;
                    gotoxy(x, y);
                    cout << ">";
                }
                else if (y < db.totalProductNum + 6) {
                    gotoxy(x, y);
                    cout << " ";
                    y += 1;
                    gotoxy(x, y);
                    cout << ">";
                }
                break;
            }

            case SUBMIT: {
                select = y - 5;
                selectfinish = true;
                break;
            }
            }
        } while (selectfinish == false);
        selectfinish = false;
        if (select == -4) {
            return 0;
        }
        else if (select == db.totalProductNum + 1) {
            addProduct();
            return 0;
        }
        gotoxy(x, y);
        cout << " ";
        gotoxy(46, y);
        cout << ">[��������]   [����]";
        int select2 = 1; // �������� ���� ����
        do {
            int n = keyControl();
            switch (n) {
            case UP: {
                gotoxy(46, y);
                cout << "                               ";
                goto manageProduct;
                break;
            }

            case DOWN: {
                gotoxy(46, y);
                cout << "                               ";
                goto manageProduct;
                break;
            }
            case LEFT: {
                if (select2 == 1) {
                    gotoxy(46, y);
                    cout << "                               ";
                    goto manageProduct;
                }
                else if (select2 == 2) {
                    select2 = 1;
                    gotoxy(59, y);
                    cout << " ";
                    gotoxy(46, y);
                    cout << ">";
                }
                break;
            }
            case RIGHT: {
                if (select2 == 2) {

                }
                else {
                    select2 = 2;
                    gotoxy(46, y);
                    cout << " ";
                    gotoxy(59, y);
                    cout << ">";
                }
                break;
            }

            case SUBMIT: {
                selectfinish = true;
                break;
            }
            }
        } while (selectfinish == false);
        selectfinish = false;
        switch (select2) {
        case 1:
            db.getProductName(select);
            updateProduct();
            Sleep(2500);
            break;
        case 2:
            db.getProductName(select);
            db.deleteDB(db.productName);
            system("cls");
            cout << "\n\n\n\n\n\n\n\t\t\t[" + db.productName + "]�׸��� �����Ǿ����ϴ�!";
            Sleep(2500);
            break;
        }
        return 0;
    }
    int addProduct() {
        char name[20];
        int price = 0;
        int inventory = 0;
        system("cls");
        cout << "\n\t\t�߰��Ͻ� ��ǰ�� ������ �Է����ּ���\n";
        cout << "\n  =====================================================================\n\n\n";
        setCursor(true);
        cout << "\t\t\t��ǰ�� : ";
        cin >> name;
        cout << "\n\n\t\t\t���� : ";
        cin >> price;
        cout << "\n\n\t\t\t��� : ";
        cin >> inventory;
        db.addProductDB(name, price, inventory);
        setCursor(false);
        cout << "\n\n\t\t\t�߰��Ǿ����ϴ�!";
        Sleep(2500);
        return 0;
    }
    int updateProduct() {
        char name[20];
        int price = 0;
        int inventory = 0;
        system("cls");
        cout << "\n\t\t[";
        db.getinfo(db.productName);
        cout << "]��ǰ�� �����Ͻ� ������ �Է����ּ���\n";
        cout << "\n  =====================================================================\n\n\n";
        setCursor(true);
        cout << "\t\t\t��ǰ�� : ";
        cin >> name;
        cout << "\n\n\t\t\t���� : ";
        cin >> price;
        cout << "\n\n\t\t\t��� : ";
        cin >> inventory;
        db.updateDB(db.productName, name, price, inventory);
        setCursor(false);
        cout << "\n\n\t\t\t�����Ǿ����ϴ�!";
        return 0;
    }
    int checkReservation() {
    checkRVWindow:
        system("cls");
        cout << endl << " [�԰� ��û ó��]";
        x = 1;
        y = 7;
        gotoxy(64, 1);
        cout << "[�ڷΰ���]";
        gotoxy(0, 0);
        cout << "\n\n\n   �й�\t\t�̸�\t\t��ǰ��\t\t\t����\n";
        cout << "\n  =============================================================================\n\n";
        db.getrequestinfo();
    checkRV:
        gotoxy(x, y);
        cout << ">";
        do {
            int n = keyControl();
            switch (n) {
            case UP: {
                if (y == 7) {
                    gotoxy(x, y);
                    cout << " ";
                    gotoxy(62, 1);
                    cout << ">";
                    y = 1;
                }
                if (y > 7) {
                    gotoxy(x, y);
                    cout << " ";
                    y -= 1;
                    gotoxy(x, y);
                    cout << ">";
                }
                break;
            }

            case DOWN: {
                if (y == 1) {
                    gotoxy(62, 1);
                    cout << " ";
                    y = 7;
                    gotoxy(x, y);
                    cout << ">";
                }
                else if (y < db.totalProductNum + 6) {
                    gotoxy(x, y);
                    cout << " ";
                    y += 1;
                    gotoxy(x, y);
                    cout << ">";
                }
                break;
            }

            case SUBMIT: {
                select = y - 6;
                selectfinish = true;
                break;
            }
            }
        } while (selectfinish == false);
        selectfinish = false;
        if (select == -5) {
            return 0;
        }
        gotoxy(x, y);
        cout << " ";
        gotoxy(62, y);
        cout << ">[����]   [����]";
        int select2 = 1; // ��û���� ���� ����
        do {
            int n = keyControl();
            switch (n) {
            case UP: {
                gotoxy(62, y);
                cout << "                               ";
                goto checkRV;
                break;
            }

            case DOWN: {
                gotoxy(62, y);
                cout << "                               ";
                goto checkRV;
                break;
            }
            case LEFT: {
                if (select2 == 1) {
                    gotoxy(62, y);
                    cout << "                               ";
                    goto checkRV;
                }
                else if (select2 == 2) {
                    select2 = 1;
                    gotoxy(71, y);
                    cout << " ";
                    gotoxy(62, y);
                    cout << ">";
                }
                break;
            }
            case RIGHT: {
                if (select2 == 2) {

                }
                else {
                    select2 = 2;
                    gotoxy(62, y);
                    cout << " ";
                    gotoxy(71, y);
                    cout << ">";
                }
                break;
            }

            case SUBMIT: {
                selectfinish = true;
                break;
            }
            }
        } while (selectfinish == false);
        selectfinish = false;
        switch (select2) {
        case 1:
            db.dealrequest(select, select2);
            system("cls");
            cout << "\n\n\n\n\n\n\n\t\t\t�����߽��ϴ�";
            break;
        case 2:
            db.dealrequest(select, select2);
            system("cls");
            cout << "\n\n\n\n\n\n\n\t\t\t�������� �ʾҽ��ϴ�";
            break;
        }
        Sleep(1000);
        goto checkRVWindow;
        return 0;
    }
};
class Buyer : public Person {
private:
    int x;
    int y;
    int select;
    boolean selectfinish = false;
    DataBase db;
public:
    Buyer() {
        job = "�����";
        db = DataBase();
    }
    ~Buyer() {

    }
    int buyProduct() {
        int shoppingbag[30][3] = { 0, };
        int cnt = 0;
        do {
            system("cls");
            x = 1;
            y = 6;
            gotoxy(52, 1);
            cout << "[�ڷΰ���]";
            gotoxy(0, 0);
            cout << "\n\n   ��ǰ��\t\t����\t\t���\n";
            cout << "\n  =====================================================================\n\n";
            db.getinfo();
            cout << "\t\t\t\t\t\t\t[����]";
            cout << "\n  =====================================================================\n\n";
            gotoxy(x, y);
            cout << "+";
        selectbuymenu:
            do {
                int n = keyControl();
                switch (n) {
                case UP: {
                    if (y == 6) {
                        gotoxy(x, y);
                        cout << " ";
                        gotoxy(50, 1);
                        cout << ">";
                        y = 1;
                    }
                    if (y == db.totalProductNum + 6) {
                        gotoxy(54, y);
                        cout << " ";
                        y -= 1;
                        gotoxy(x, y);
                        cout << "+";
                    }
                    else if (y > 6) {
                        gotoxy(x, y);
                        cout << " ";
                        y -= 1;
                        gotoxy(x, y);
                        cout << "+";
                    }

                    break;
                }

                case DOWN: {
                    if (y == 1) {
                        gotoxy(50, 1);
                        cout << " ";
                        y = 6;
                        gotoxy(x, y);
                        cout << "+";
                    }
                    else if (y < db.totalProductNum + 5) {
                        gotoxy(x, y);
                        cout << " ";
                        y += 1;
                        gotoxy(x, y);
                        cout << "+";
                    }
                    else if (y == db.totalProductNum + 5) {
                        gotoxy(x, y);
                        cout << " ";
                        y += 1;
                        gotoxy(54, y);
                        cout << ">";
                    }
                    break;
                }

                case SUBMIT: {
                    select = y - 5;
                    if (select > db.totalProductNum) {
                        select = -1;
                    }
                    selectfinish = true;
                    break;
                }
                }
            } while (selectfinish == false);
            selectfinish = false;
            if (select == -4) {
                return 0;
            }
            else if (select == -1) {
                system("cls");
                int sum = 0;
                cout << "\n ============================================\n";
                cout << "                  ��ǥ                  ";
                cout << "\n ============================================\n";
                for (int i = 0; i < sizeof(shoppingbag) / sizeof(shoppingbag[0]); i++) {
                    if (shoppingbag[i][0] == 0) {
                        break;
                    }
                    else {
                        db.getinfoName(shoppingbag[i][0]);
                        printf("%d��\t\t%d��\n", shoppingbag[i][1], shoppingbag[i][2]);
                        db.updateDB(shoppingbag[i][0], db.getinfo(db.productName, 3) - shoppingbag[i][2]);
                        sum += shoppingbag[i][1] * shoppingbag[i][2];
                    }
                }
                cout << "\n   �ѱݾ� : " << sum << "��" << endl;
                cout << "\n   Ȯ���ϼ����� ����Ű�� �����ּ���";
                do {
                    int n = keyControl();
                    switch (n) {
                    case SUBMIT: {
                        selectfinish = true;
                        break;
                    }
                    }
                } while (selectfinish == false);
                selectfinish = false;
                return 0;
            }
            else {
                db.getProductName(select);
                //cout << db.productName << "����";
                for (int i = 0; i < sizeof(shoppingbag) / sizeof(shoppingbag[0]); i++) {
                    if (shoppingbag[i][0] == select) {
                        if (shoppingbag[i][2] != db.getinfo(db.productName, 3)) {
                            shoppingbag[i][2] += 1;
                        }
                        break;
                    }
                    else if (shoppingbag[i][0] == 0) {
                        shoppingbag[cnt][0] = select;
                        shoppingbag[cnt][1] = db.getinfo(db.productName, 2);
                        shoppingbag[cnt][2] = 1;
                        cnt++;
                        break;
                    }
                }
                gotoxy(x - 1, db.totalProductNum + 9);
                for (int i = 0; i < sizeof(shoppingbag) / sizeof(shoppingbag[0]); i++) {
                    if (shoppingbag[i][0] == 0) {
                        break;
                    }
                    else {
                        db.getinfoName(shoppingbag[i][0]);
                        printf("%d\t\t%d\n", shoppingbag[i][1], shoppingbag[i][2]);
                    }
                }
                goto selectbuymenu;
            }
        } while (select == -4);
        return 0;
    }
    int requestProduct() {
        system("cls");
        int studentNum = 0;
        char studentName[20];
        char productName[20];
        int productNum = 0;
        system("cls");
        cout << "\n\t\t�԰� ���Ͻô� ��ǰ�� ������ �Է����ּ���\n";
        cout << "\n  =====================================================================\n\n\n";
        setCursor(true);
        cout << "\t\t\t�й� : ";
        cin >> studentNum;
        cout << "\n\n\t\t\t�̸� : ";
        cin >> studentName;
        cout << "\n\n\t\t\t��ǰ�� : ";
        cin >> productName;
        cout << "\n\n\t\t\t���� : ";
        cin >> productNum;
        db.addRequestDB(studentNum, studentName, productName, productNum);
        setCursor(false);
        cout << "\n\n\t\t\t��û�� �Ϸ�Ǿ����ϴ�!";
        Sleep(2500);
        return 0;
    }
    int showReservation() {
        system("cls");
        cout << endl << "[�԰�Ȯ��]";
        x = 1;
        y = 7;
        gotoxy(68, 1);
        cout << "> [�ڷΰ���]";
        gotoxy(0, 0);
        cout << "\n\n\n   �й�\t\t�̸�\t\t��ǰ��\t\t\t����\n";
        cout << "\n  =============================================================================\n\n";
        db.getrequestinfo_2();
        do {
            int n = keyControl();
            switch (n) {
            case SUBMIT: {
                select = -5;
                selectfinish = true;
                break;
            }
            }
        } while (selectfinish == false);
        selectfinish = false;
        if (select == -5) {
            return 0;
        }
        return 0;
    }
    int recommendMenu() {
        system("cls");
        cout << "\n          �ڡڡڡڡڡڡڡڡڡڲ�������õ��ڡڡڡڡڡڡڡڡڡ�";
        x = 1;
        y = 7;
        gotoxy(68, 1);
        cout << "> [�ڷΰ���]";
        gotoxy(0, 0);
        cout << "\n\n\n  =============================================================================\n\n";
        // ���⿡ �ڵ�
        cout << "          <õ������> ���� + �����ֽ�" << endl << endl;
        cout << "          <��§��§> �ƹݼ���� + �����ֽ�" << endl << endl;
        cout << "          <���ڿ������> ����Ĩ + �����" << endl << endl;
        cout << "          <����� �ѳ�> ����+ġŲ+�����ֽ�" << endl << endl;
        cout << "          <�ع���Ƽ> ��¡��Ĩ + �����" << endl << endl;
        cout << "          <��������> ���� + ������" << endl << endl;
        cout << "          ��ſ� ������Ȱ �ϼ���!" << endl << endl;
        do {
            int n = keyControl();
            switch (n) {
            case SUBMIT: {
                select = -5;
                selectfinish = true;
                break;
            }
            }
        } while (selectfinish == false);
        selectfinish = false;
        if (select == -5) {
            return 0;
        }
        return 0;
    }
};
int main()
{
    int select;
    boolean selectfinish = false;
    int x = 26;
    int y = 7;
    connectDB();
    setCursor(false);
selectuser:
    y = 7;
    select = NULL;
    setCursor(false);
    system("cls");
    cout << "\n\n\t\t\t����Ͻ� ����� �������ּ���.\n";
    cout << "\n  =====================================================================";
    gotoxy(x - 2, y);
    cout << "> ������ ���α׷�";
    gotoxy(x, y + 2);
    cout << "����� ���α׷�";
    gotoxy(x, y + 4);
    cout << "����";
    do {
        int n = keyControl();
        switch (n) {
        case UP: {
            if (y > 7) {
                gotoxy(x - 2, y);
                cout << " ";
                y -= 2;
                gotoxy(x - 2, y);
                cout << ">";
            }
            break;
        }

        case DOWN: {
            if (y < 11) {
                gotoxy(x - 2, y);
                cout << " ";
                y += 2;
                gotoxy(x - 2, y);
                cout << ">";
            }
            break;
        }

        case SUBMIT: {
            select = (y - 5) / 2;
            selectfinish = true;
            break;
        }
        }
    } while (selectfinish == false);
    selectfinish = false;
    switch (select)
    {
    case 1:
    {
        Manager owner = Manager();
        system("cls");
        int password;
        cout << "\n\n\n\n\n\n\n\t\t\t��й�ȣ �Է� : ";
        setCursor(true);
        cin >> password;
        setCursor(false);
        if (owner.checkPassword(password) == -1) {
            SetCursor(false);
            for (int i = 3; i >= 1; i--) {
                system("cls");
                cout << "\n\n\n\n\n\n\n\t\t\t��й�ȣ�� Ʋ�Ƚ��ϴ�!";
                cout << "\n\n\t\t\t" << i << "�� �� ���� ȭ������ ���ư��ϴ�";
                Sleep(1000);
            }
            goto selectuser;
        }

        PrintLoading("������ ���α׷� ������");
    managerselect:
        system("cls");
        y = 7;
        select = NULL;
        cout << "\n[" << owner.job << "]"; // ��ӵ� job �޾ƿ���
        cout << "\n\t\t\t<�̸� �ǰ�����>\n";
        cout << "\n  =====================================================================";
        gotoxy(x - 2, y);
        cout << "> ��ǰ����";
        gotoxy(x, y + 2);
        cout << "����Ȯ��";
        gotoxy(x, y + 4);
        cout << "������";
        do {
            int n = keyControl();
            switch (n) {
            case UP: {
                if (y > 7) {
                    gotoxy(x - 2, y);
                    cout << " ";
                    y -= 2;
                    gotoxy(x - 2, y);
                    cout << ">";
                }
                break;
            }

            case DOWN: {
                if (y < 11) {
                    gotoxy(x - 2, y);
                    cout << " ";
                    y += 2;
                    gotoxy(x - 2, y);
                    cout << ">";
                }
                break;
            }

            case SUBMIT: {
                select = (y - 5) / 2;
                selectfinish = true;
                break;
            }
            }
        } while (selectfinish == false);
        selectfinish = false;
        switch (select)
        {
        case 1:
            owner.manageProduct();
            goto managerselect;
            break;
        case 2:
            owner.checkReservation();
            goto managerselect;
            break;
        case 3:
            PrintLoading("������ ���α׷� ����������");
            goto selectuser;
            break;
        default:
            cout << "�Է½���" << endl; break;
        }
        break;
    }
    case 2:
    {
        Buyer buyer = Buyer();
        PrintLoading("����� ���α׷� ������");

    buyerselect:
        y = 7;
        select = NULL;
        system("cls");
        cout << "\n[" << buyer.job << "]"; // ��ӵ� job �޾ƿ���
        cout << "\n\t\t\t<�̸� �ǰ�����>\n";
        cout << "\n  =====================================================================";
        gotoxy(x - 2, y);
        cout << "> ��ǰ����";
        gotoxy(x, y + 2);
        cout << "�԰��û";
        gotoxy(x, y + 4);
        cout << "�԰�Ȯ��";
        gotoxy(x, y + 6);
        cout << "��������õ��";
        gotoxy(x, y + 8);
        cout << "������";
        do {
            int n = keyControl();
            switch (n) {
            case UP: {
                if (y > 7) {
                    gotoxy(x - 2, y);
                    cout << " ";
                    y -= 2;
                    gotoxy(x - 2, y);
                    cout << ">";
                }
                break;
            }

            case DOWN: {
                if (y < 15) {
                    gotoxy(x - 2, y);
                    cout << " ";
                    y += 2;
                    gotoxy(x - 2, y);
                    cout << ">";
                }
                break;
            }

            case SUBMIT: {
                select = (y - 5) / 2;
                selectfinish = true;
                break;
            }
            }
        } while (selectfinish == false);
        selectfinish = false;
        switch (select)
        {
        case 1:
            buyer.buyProduct();
            goto buyerselect;
            break;
        case 2:
            buyer.requestProduct();
            goto buyerselect;
            break;
        case 3:
            buyer.showReservation();
            goto buyerselect;
            break;
        case 4:
            buyer.recommendMenu();
            goto buyerselect;
            break;
        case 5: PrintLoading("����� ���α׷� ����������");
            goto selectuser;
            break;
        default: cout << "�Է½���" << endl;
            break;
        }
        break;
    }
    case 3:
        return 0; break;
    default:
        cout << "�Է½���" << endl; break;
    }

menu:
    system("cls");
    cout << "\n\n\t\t\t\t\t\t<�̸� �ǰ� ����>\n";
    cout << "\n\t\t\t\t\t=================================\n\n\n";
    cout << "\t\t\t\t\t   1.����\n";
    cout << "\t\t\t\t\t   2.����\n";
    cout << "\t\t\t\t\t   3.����\n\n";
    cout << "\t\t\t\t\t   >>>  ";
    int select1;
    cin >> select1;
    switch (select1)
    {
    case 1:
        PrintLoading("���������α׷� ������");
    ss:
        system("cls");
        cout << "\n\n\t\t\t\t\t\t<���� ���α׷�>\n";
        cout << "\n\t\t\t\t\t=================================\n\n\n";
        cout << "\t\t\t\t\t   1.���ư���\n\n";
        cout << "\t\t\t\t\t   >>>  ";
        int select2;
        cin >> select2;
        switch (select2)
        {
        case 1:
            goto menu;
        }
    }
    // �����ͺ��̽��� ���� ����
    //mysql_close(&Conn);
}
void PrintLoading(string text) {
    for (int i = 0; i < 3; i++) {
        system("cls");
        cout << "\n\n\n\n\n\n\n\t\t\t" << text + ".";
        Sleep(300);
        system("cls");
        cout << "\n\n\n\n\n\n\n\t\t\t" << text + "..";
        Sleep(300);
        system("cls");
        cout << "\n\n\n\n\n\n\n\t\t\t" << text + "...";
        Sleep(300);
    }
}
void gotoxy(int x, int y) {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(consoleHandle, pos);
}

int keyControl() {
    char c;
    while (1) {
        if (_kbhit()) {               // 2. while���ȿ��� Ű���� ������ �� if���� ����ȴ�.
            c = _getch();           // 3. ����Ű�� �Է��� �� 224 00 �� ���ۿ� �ִ�. 224���� ���ش�. 
            if (c == -32) {           // 4. -32�� �ԷµǸ�
                c = _getch();        // 5. ���� �� 00�� �Ǻ��Ͽ� �¿���� ���
                switch (c) {
                case 75:
                    return LEFT;
                    break;
                case 77:
                    return RIGHT;
                    break;
                case 72:
                    return UP;
                    break;
                case 80:
                    return DOWN;
                    break;
                }
            }
            else if (c == 13) {
                return SUBMIT;
            }
        }
    }
}
void connectDB() {
    mysql_init(&Conn);      // MySQL ���� �ʱ�ȭ

    // �����ͺ��̽��� ����
    ConnPtr = mysql_real_connect(&Conn, "localhost", "root", "secret", "products", 3306, NULL, 0);

    if (ConnPtr == NULL) // ���� ��� Ȯ��. NULL�� ��� ���� �����Ѱ�.
    {
        cout << "error : " << mysql_error(&Conn);
    }
    else {
    }
    mysql_query(ConnPtr, "set session character_set_connection=euckr;");
    mysql_query(ConnPtr, "set session character_set_results=euckr;");
    mysql_query(ConnPtr, "set session character_set_client=euckr;");
}
void setCursor(boolean state) {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO ConsoleCursor;
    ConsoleCursor.bVisible = state;
    ConsoleCursor.dwSize = 1;
    SetConsoleCursorInfo(consoleHandle, &ConsoleCursor);
}