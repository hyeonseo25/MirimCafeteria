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
        char* Query = "SELECT * FROM product";      // 세미콜론을 제외하고 쿼리문 작성
        Stat = mysql_query(ConnPtr, Query);         // 쿼리 요청 및 성공여부 받아오기
        if (Stat != 0)
        {
            cout << stderr << "error : " << mysql_error(&Conn);
        }
        else {
            Result = mysql_store_result(ConnPtr);           // 결과 확인하기
            while ((Row = mysql_fetch_row(Result)) != NULL) // 결과 출력하기
            {
                totalProductNum++; // DB의 총 상품갯수를 알 수 있음
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
            mysql_free_result(Result);                      // 결과 비우기
        }
    }
    void getinfo(string name) {
        string Query = "";     // 세미콜론을 제외하고 쿼리문 작성
        Query += "SELECT * FROM product where name = '";
        Query += name;
        Query += "'";
        Stat = mysql_query(ConnPtr, Query.c_str());         // 쿼리 요청 및 성공여부 받아오기
        if (Stat != 0)
        {
            cout << stderr << "error : " << mysql_error(&Conn);
        }
        else {
            Result = mysql_store_result(ConnPtr);           // 결과 확인하기
            while ((Row = mysql_fetch_row(Result)) != NULL) // 결과 출력하기
            {
                printf("%s %s원 %s개", Row[0], Row[1], Row[2]);
            }
            mysql_free_result(Result);                      // 결과 비우기
        }
    }
    void getinfoName(int num) {
        getProductName(num);
        string Query = "";     // 세미콜론을 제외하고 쿼리문 작성
        Query += "SELECT * FROM product where name = '";
        Query += this->productName;
        Query += "'";
        Stat = mysql_query(ConnPtr, Query.c_str());         // 쿼리 요청 및 성공여부 받아오기
        if (Stat != 0)
        {
            cout << stderr << "error : " << mysql_error(&Conn);
        }
        else {
            Result = mysql_store_result(ConnPtr);           // 결과 확인하기
            while ((Row = mysql_fetch_row(Result)) != NULL) // 결과 출력하기
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
            mysql_free_result(Result);                      // 결과 비우기
        }
    }
    int getinfo(string name, int num) {
        string Query = "";     // 세미콜론을 제외하고 쿼리문 작성
        Query += "SELECT * FROM product where name = '";
        Query += name;
        Query += "'";
        Stat = mysql_query(ConnPtr, Query.c_str());         // 쿼리 요청 및 성공여부 받아오기
        if (Stat != 0)
        {
            cout << stderr << "error : " << mysql_error(&Conn);
        }
        else {
            Result = mysql_store_result(ConnPtr);           // 결과 확인하기
            while ((Row = mysql_fetch_row(Result)) != NULL) // 결과 출력하기
            {
                if (num == 2) {
                    return atoi(Row[1]);
                }
                else if (num == 3) {
                    return atoi(Row[2]);
                }
            }
            mysql_free_result(Result);                      // 결과 비우기
        }
    }
    void getrequestinfo() {
        this->totalProductNum = 0;
        char* Query = "SELECT * FROM request";      // 세미콜론을 제외하고 쿼리문 작성
        Stat = mysql_query(ConnPtr, Query);         // 쿼리 요청 및 성공여부 받아오기
        if (Stat != 0)
        {
            cout << stderr << "error : " << mysql_error(&Conn);
        }
        else {
            Result = mysql_store_result(ConnPtr);           // 결과 확인하기
            while ((Row = mysql_fetch_row(Result)) != NULL) // 결과 출력하기
            {
                if (atoi(Row[5]) != 1 && atoi(Row[5]) != 2) {
                    totalProductNum++; // DB의 총 상품갯수를 알 수 있음
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
            mysql_free_result(Result);                      // 결과 비우기
        }
    }
    void getrequestinfo_2() {
        this->totalProductNum = 0;
        char* Query = "SELECT * FROM request";      // 세미콜론을 제외하고 쿼리문 작성
        Stat = mysql_query(ConnPtr, Query);         // 쿼리 요청 및 성공여부 받아오기
        if (Stat != 0)
        {
            cout << stderr << "error : " << mysql_error(&Conn);
        }
        else {
            Result = mysql_store_result(ConnPtr);           // 결과 확인하기
            while ((Row = mysql_fetch_row(Result)) != NULL) // 결과 출력하기
            {
                if (atoi(Row[5]) == 1) {
                    totalProductNum++; // DB의 총 상품갯수를 알 수 있음
                    if ((((string)Row[3]).length()) / 2 <= 3) {
                        printf("   %s\t\t%s\t\t%s\t\t\t%s\t\t승인됨\n", Row[1], Row[2], Row[3], Row[4]);
                    }
                    else if ((((string)Row[3]).length()) / 2 <= 7) {
                        printf("   %s\t\t%s\t\t%s\t\t%s\t\t승인됨\n", Row[1], Row[2], Row[3], Row[4]);
                    }
                    else {
                        printf("   %s\t\t%s\t\t%s\t%s\t\t승인됨\n", Row[1], Row[2], Row[3], Row[4]);
                    }
                }
                else if (atoi(Row[5]) == 2) {
                    totalProductNum++; // DB의 총 상품갯수를 알 수 있음
                    if ((((string)Row[3]).length()) / 2 <= 3) {
                        printf("   %s\t\t%s\t\t%s\t\t\t%s\t\t거절됨\n", Row[1], Row[2], Row[3], Row[4]);
                    }
                    else if ((((string)Row[3]).length()) / 2 <= 7) {
                        printf("   %s\t\t%s\t\t%s\t\t%s\t\t거절됨\n", Row[1], Row[2], Row[3], Row[4]);
                    }
                    else {
                        printf("   %s\t\t%s\t\t%s\t%s\t\t거절됨\n", Row[1], Row[2], Row[3], Row[4]);
                    }
                }
            }
            mysql_free_result(Result);                      // 결과 비우기
        }
    }
    void getProductName(int num) {
        int count = 1;
        char* Query = "SELECT * FROM product";      // 세미콜론을 제외하고 쿼리문 작성
        Stat = mysql_query(ConnPtr, Query);         // 쿼리 요청 및 성공여부 받아오기
        if (Stat != 0)
        {
            cout << stderr << "error : " << mysql_error(&Conn);
        }
        else {
            Result = mysql_store_result(ConnPtr);           // 결과 확인하기
            while ((Row = mysql_fetch_row(Result)) != NULL) // 결과 출력하기
            {
                if (count == num) {
                    this->productName = Row[0];
                    break;
                }
                count++;
            }
            mysql_free_result(Result);                      // 결과 비우기
        }
    }
    void dealrequest(int num, int deal) {
        int count = 1;
        string ownnum = "";
        char* Query = "SELECT * FROM request";      // 세미콜론을 제외하고 쿼리문 작성
        Stat = mysql_query(ConnPtr, Query);         // 쿼리 요청 및 성공여부 받아오기
        if (Stat != 0)
        {
            cout << stderr << "error : " << mysql_error(&Conn);
        }
        else {
            Result = mysql_store_result(ConnPtr);           // 결과 확인하기
            while ((Row = mysql_fetch_row(Result)) != NULL) // 결과 출력하기
            {
                if (atoi(Row[5]) != 1 && atoi(Row[5]) != 2) {
                    if (count == num) {
                        ownnum = (string)Row[0];
                        break;
                    }
                    count++;
                }
            }
            mysql_free_result(Result);                      // 결과 비우기
        }
        char temp[10];
        string Query2 = "";     // 세미콜론을 제외하고 쿼리문 작성
        Query2 += "UPDATE request SET approval = ";
        _itoa(deal, temp, 10);
        Query2 += temp;
        Query2 += " WHERE serialNum = ";
        Query2 += ownnum;
        Stat = mysql_query(ConnPtr, Query2.c_str());         // 쿼리 요청 및 성공여부 받아오기
        if (Stat != 0)
        {
            cout << stderr << "error : " << mysql_error(&Conn);
        }
    }

    int addProductDB(char* name = "productname", int price = 0, int inventory = 0) {
        char temp[10];
        string Query = "";     // 세미콜론을 제외하고 쿼리문 작성
        Query += "insert into product(name,price,inventory) values ('";
        Query += name;
        Query += "',";
        _itoa(price, temp, 10);
        Query += temp;
        Query += ",";
        _itoa(inventory, temp, 10);
        Query += temp;
        Query += ")";
        Stat = mysql_query(ConnPtr, Query.c_str());         // 쿼리 요청 및 성공여부 받아오기
        if (Stat != 0)
        {
            cout << stderr << "error : " << mysql_error(&Conn);
        }
        return 0;
    }
    int deleteDB(string name) {
        string Query = "";     // 세미콜론을 제외하고 쿼리문 작성
        Query += "delete from product where name='";
        Query += name;
        Query += "'";
        Stat = mysql_query(ConnPtr, Query.c_str());         // 쿼리 요청 및 성공여부 받아오기
        if (Stat != 0)
        {
            cout << stderr << "error : " << mysql_error(&Conn);
        }
        return 0;
    }
    int updateDB(string name, string new_name, int price, int inventory) {
        char temp[10];
        string Query = "";     // 세미콜론을 제외하고 쿼리문 작성
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
        Stat = mysql_query(ConnPtr, Query.c_str());         // 쿼리 요청 및 성공여부 받아오기
        if (Stat != 0)
        {
            cout << stderr << "error : " << mysql_error(&Conn);
        }
        return 0;
    }
    int updateDB(int num, int inventory) {
        getProductName(num);
        char temp[10];
        string Query = "";     // 세미콜론을 제외하고 쿼리문 작성
        Query += "UPDATE product SET inventory = ";
        _itoa(inventory, temp, 10);
        Query += temp;
        Query += " WHERE name = '";
        Query += this->productName;
        Query += "'";
        Stat = mysql_query(ConnPtr, Query.c_str());         // 쿼리 요청 및 성공여부 받아오기
        if (Stat != 0)
        {
            cout << stderr << "error : " << mysql_error(&Conn);
        }
        return 0;
    }
    int addRequestDB(int studentNum, string studentName, string productName, int productNum) {
        char temp[10];
        string Query = "";     // 세미콜론을 제외하고 쿼리문 작성
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
        Stat = mysql_query(ConnPtr, Query.c_str());         // 쿼리 요청 및 성공여부 받아오기
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
class Manager : public Person { // 상속
private:
    int password = 5588;
    int x;
    int y;
    int select;
    boolean selectfinish = false;
    DataBase db;
public:
    Manager() {
        job = "관리자";
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
        cout << "[뒤로가기]";
        gotoxy(0, 0);
        cout << "\n\n   상품명\t\t가격\t\t재고\n";
        cout << "\n  =====================================================================\n\n";
        db.getinfo();
        cout << "   [+상품추가]";
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
        cout << ">[정보수정]   [삭제]";
        int select2 = 1; // 정보수정 삭제 선택
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
            cout << "\n\n\n\n\n\n\n\t\t\t[" + db.productName + "]항목이 삭제되었습니다!";
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
        cout << "\n\t\t추가하실 상품의 정보를 입력해주세요\n";
        cout << "\n  =====================================================================\n\n\n";
        setCursor(true);
        cout << "\t\t\t상품명 : ";
        cin >> name;
        cout << "\n\n\t\t\t가격 : ";
        cin >> price;
        cout << "\n\n\t\t\t재고 : ";
        cin >> inventory;
        db.addProductDB(name, price, inventory);
        setCursor(false);
        cout << "\n\n\t\t\t추가되었습니다!";
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
        cout << "]상품의 수정하실 정보를 입력해주세요\n";
        cout << "\n  =====================================================================\n\n\n";
        setCursor(true);
        cout << "\t\t\t상품명 : ";
        cin >> name;
        cout << "\n\n\t\t\t가격 : ";
        cin >> price;
        cout << "\n\n\t\t\t재고 : ";
        cin >> inventory;
        db.updateDB(db.productName, name, price, inventory);
        setCursor(false);
        cout << "\n\n\t\t\t수정되었습니다!";
        return 0;
    }
    int checkReservation() {
    checkRVWindow:
        system("cls");
        cout << endl << " [입고 요청 처리]";
        x = 1;
        y = 7;
        gotoxy(64, 1);
        cout << "[뒤로가기]";
        gotoxy(0, 0);
        cout << "\n\n\n   학번\t\t이름\t\t상품명\t\t\t수량\n";
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
        cout << ">[승인]   [삭제]";
        int select2 = 1; // 요청승인 삭제 선택
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
            cout << "\n\n\n\n\n\n\n\t\t\t승인했습니다";
            break;
        case 2:
            db.dealrequest(select, select2);
            system("cls");
            cout << "\n\n\n\n\n\n\n\t\t\t승인하지 않았습니다";
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
        job = "사용자";
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
            cout << "[뒤로가기]";
            gotoxy(0, 0);
            cout << "\n\n   상품명\t\t가격\t\t재고\n";
            cout << "\n  =====================================================================\n\n";
            db.getinfo();
            cout << "\t\t\t\t\t\t\t[구매]";
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
                cout << "                  명세표                  ";
                cout << "\n ============================================\n";
                for (int i = 0; i < sizeof(shoppingbag) / sizeof(shoppingbag[0]); i++) {
                    if (shoppingbag[i][0] == 0) {
                        break;
                    }
                    else {
                        db.getinfoName(shoppingbag[i][0]);
                        printf("%d원\t\t%d개\n", shoppingbag[i][1], shoppingbag[i][2]);
                        db.updateDB(shoppingbag[i][0], db.getinfo(db.productName, 3) - shoppingbag[i][2]);
                        sum += shoppingbag[i][1] * shoppingbag[i][2];
                    }
                }
                cout << "\n   총금액 : " << sum << "원" << endl;
                cout << "\n   확인하셨으면 엔터키를 눌러주세요";
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
                //cout << db.productName << "선택";
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
        cout << "\n\t\t입고를 원하시는 상품의 정보를 입력해주세요\n";
        cout << "\n  =====================================================================\n\n\n";
        setCursor(true);
        cout << "\t\t\t학번 : ";
        cin >> studentNum;
        cout << "\n\n\t\t\t이름 : ";
        cin >> studentName;
        cout << "\n\n\t\t\t상품명 : ";
        cin >> productName;
        cout << "\n\n\t\t\t수량 : ";
        cin >> productNum;
        db.addRequestDB(studentNum, studentName, productName, productNum);
        setCursor(false);
        cout << "\n\n\t\t\t신청이 완료되었습니다!";
        Sleep(2500);
        return 0;
    }
    int showReservation() {
        system("cls");
        cout << endl << "[입고확인]";
        x = 1;
        y = 7;
        gotoxy(68, 1);
        cout << "> [뒤로가기]";
        gotoxy(0, 0);
        cout << "\n\n\n   학번\t\t이름\t\t상품명\t\t\t수량\n";
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
        cout << "\n          ★★★★★★★★★★꿀조합추천기★★★★★★★★★★";
        x = 1;
        y = 7;
        gotoxy(68, 1);
        cout << "> [뒤로가기]";
        gotoxy(0, 0);
        cout << "\n\n\n  =============================================================================\n\n";
        // 여기에 코드
        cout << "          <천원정식> 몽쉘 + 망고주스" << endl << endl;
        cout << "          <단짠단짠> 맥반석계란 + 망고주스" << endl << endl;
        cout << "          <초코엔흰우유> 초코칩 + 흰우유" << endl << endl;
        cout << "          <든든한 한끼> 만두+치킨+망고주스" << endl << endl;
        cout << "          <해물파티> 오징어칩 + 새우깡" << endl << endl;
        cout << "          <수현정식> 비요뜨 + 빼빼로" << endl << endl;
        cout << "          즐거운 매점생활 하세요!" << endl << endl;
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
    cout << "\n\n\t\t\t사용하실 기능을 선택해주세요.\n";
    cout << "\n  =====================================================================";
    gotoxy(x - 2, y);
    cout << "> 관리자 프로그램";
    gotoxy(x, y + 2);
    cout << "사용자 프로그램";
    gotoxy(x, y + 4);
    cout << "종료";
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
        cout << "\n\n\n\n\n\n\n\t\t\t비밀번호 입력 : ";
        setCursor(true);
        cin >> password;
        setCursor(false);
        if (owner.checkPassword(password) == -1) {
            SetCursor(false);
            for (int i = 3; i >= 1; i--) {
                system("cls");
                cout << "\n\n\n\n\n\n\n\t\t\t비밀번호가 틀렸습니다!";
                cout << "\n\n\t\t\t" << i << "초 뒤 메인 화면으로 돌아갑니다";
                Sleep(1000);
            }
            goto selectuser;
        }

        PrintLoading("관리자 프로그램 접근중");
    managerselect:
        system("cls");
        y = 7;
        select = NULL;
        cout << "\n[" << owner.job << "]"; // 상속된 job 받아오기
        cout << "\n\t\t\t<미림 건강매점>\n";
        cout << "\n  =====================================================================";
        gotoxy(x - 2, y);
        cout << "> 상품관리";
        gotoxy(x, y + 2);
        cout << "예약확인";
        gotoxy(x, y + 4);
        cout << "나가기";
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
            PrintLoading("관리자 프로그램 접근해제중");
            goto selectuser;
            break;
        default:
            cout << "입력실패" << endl; break;
        }
        break;
    }
    case 2:
    {
        Buyer buyer = Buyer();
        PrintLoading("사용자 프로그램 접근중");

    buyerselect:
        y = 7;
        select = NULL;
        system("cls");
        cout << "\n[" << buyer.job << "]"; // 상속된 job 받아오기
        cout << "\n\t\t\t<미림 건강매점>\n";
        cout << "\n  =====================================================================";
        gotoxy(x - 2, y);
        cout << "> 상품구매";
        gotoxy(x, y + 2);
        cout << "입고요청";
        gotoxy(x, y + 4);
        cout << "입고확인";
        gotoxy(x, y + 6);
        cout << "꿀조합추천기";
        gotoxy(x, y + 8);
        cout << "나가기";
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
        case 5: PrintLoading("사용자 프로그램 접근해제중");
            goto selectuser;
            break;
        default: cout << "입력실패" << endl;
            break;
        }
        break;
    }
    case 3:
        return 0; break;
    default:
        cout << "입력실패" << endl; break;
    }

menu:
    system("cls");
    cout << "\n\n\t\t\t\t\t\t<미림 건강 매점>\n";
    cout << "\n\t\t\t\t\t=================================\n\n\n";
    cout << "\t\t\t\t\t   1.관리\n";
    cout << "\t\t\t\t\t   2.구매\n";
    cout << "\t\t\t\t\t   3.종료\n\n";
    cout << "\t\t\t\t\t   >>>  ";
    int select1;
    cin >> select1;
    switch (select1)
    {
    case 1:
        PrintLoading("관리자프로그램 접근중");
    ss:
        system("cls");
        cout << "\n\n\t\t\t\t\t\t<관리 프로그램>\n";
        cout << "\n\t\t\t\t\t=================================\n\n\n";
        cout << "\t\t\t\t\t   1.돌아가기\n\n";
        cout << "\t\t\t\t\t   >>>  ";
        int select2;
        cin >> select2;
        switch (select2)
        {
        case 1:
            goto menu;
        }
    }
    // 데이터베이스와 연결 해제
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
        if (_kbhit()) {               // 2. while문안에서 키보드 눌렸을 시 if문이 실행된다.
            c = _getch();           // 3. 방향키가 입력됬을 때 224 00 이 버퍼에 있다. 224부터 빼준다. 
            if (c == -32) {           // 4. -32로 입력되면
                c = _getch();        // 5. 뒤의 값 00을 판별하여 좌우상하 출력
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
    mysql_init(&Conn);      // MySQL 정보 초기화

    // 데이터베이스와 연결
    ConnPtr = mysql_real_connect(&Conn, "localhost", "root", "secret", "products", 3306, NULL, 0);

    if (ConnPtr == NULL) // 연결 결과 확인. NULL일 경우 연결 실패한것.
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