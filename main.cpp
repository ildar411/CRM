#include "widget.h"
#include <QApplication>
#include <QtSql>
#include <QSqlQuery>
#include <iostream>
#include <QString>
#include <QDate>
#include <QTime>
#include <QDateTime>
using namespace std;

ostream& operator << (ostream &stream, const QString &str)
{
    return stream << str.toStdString();
}
istream& operator >> (istream &stream, const QString& str)
{
    stream >> str;
    return stream;
}
class DB_interaction {
public:
    void add_on_stock_trade_unit(int, QString, QString);//добавление на продажу ivan tz
    void Stock_Unit_add(int, QDate);//ivan tz
    void changes_of_price();//переменные какие будут подумать скидки и тд
    double profit_from_table();//переменные прибыль со стола
    DB_interaction();//подумать над разными конструкторами этого класса must have
    ~DB_interaction();//деструктор must have
    void client_add(QString, QString, QString, QString, QString);
    void employee_add(QString, QString, QString, QDate, QDate);
    double profit_from_employee();//прибыль со сотрудника
    void change_s_t_p();//запись в историю цен изменения и даты изменений
    void deduct_from_stock();//убрать из склада то что идет на stock trade unit
    double method_of_price();//метод формирования цены возрашает ценник

    double summ_of_employee();//сумма продаж одного сотрудника

    void datetime_of_seat();//выставка времени посадки
    double sum_of_order();//выставка счета

    void new_employee();//новый сотрудник
    void delete_employee();//удоление сотрудника

    void add_table();//добавление стола
    void delete_table();//удаление стола
    void change_table();//изменение физ свойств стола
    QSqlDatabase crmDB;
private:

};

class Status {

public:
    int get_status_by_statusName(QString status_name) {

        QSqlQuery select_status_id("SELECT id FROM Status WHERE name = ?");
        select_status_id.addBindValue(status_name);

        int status_id = 0;
        while (select_status_id.next()) {
            status_id = select_status_id.value(0).toInt();
        }

        return status_id;

    }

};

class Employee {

public:


    Employee() {}

    void hire (QString name,
              QString surname = NULL,
              QString patronymic = NULL,
              QString email = NULL,
              QString phonenumber = NULL,
              QString status_name = NULL)
    {

        QSqlQuery query;
        query.prepare("insert into Employee(name, surname, patronymic, email, phonenumber, Status_id, date_hired)"
                      "values(?, ?, ?, ?, ?, ?, ?)");

        query.addBindValue(name);
        query.addBindValue(surname);
        query.addBindValue(patronymic);
        query.addBindValue(email);
        query.addBindValue(phonenumber);

        int status_id = status.get_status_by_statusName(status_name);
        query.addBindValue(status_id);

        QDate currentDate = QDate::currentDate();
        query.addBindValue(currentDate);

        query.exec();
    }

    void fire (int Employee_id,
               QDate date = QDate::currentDate())
    {
        QSqlQuery delete_employee;
        delete_employee.prepare("UPDATE Employee SET date_fired = ? WHERE id = ?");

        delete_employee.addBindValue(date);
        delete_employee.addBindValue(Employee_id);

        delete_employee.exec();
    }



private:
    Status status;

};




void employee_add(QString name, QString surname, QString patronymic, QDate date_hired, QDate date_fired = NULL)
{
    QSqlQuery query;
    cin >> name;
    cin >> surname;
    cin >> PATRONYMIC;

}

DB_interaction::DB_interaction()
{
    crmDB = QSqlDatabase::addDatabase("QMYSQL", "CRM_ivan_1.2");
    bool ok = crmDB.open();
    if (ok == false)
        exit(-1);


}
//void DB_interaction::client_add(QString name = NULL,
//                                QString surname = NULL,
//                                QString patronymic = NULL,
//                                QString email = NULL,
//                                QString phonenumber = NULL )
//{
//    QSqlQuery query;
//    cin >> name;
//    cin >> surname;
//    cin >> patronymic;
//    cin >> email;
//    cin >> phonenumber;

//    query.prepare("insert into Client(name, surname, patronymic, email,"
//                  "phonenumber)"
//                  "values(?, ?, ?, ?, ?");
//    query.addBindValue(name);
//    query.addBindValue(surname);
//    query.addBindValue(patronymic);
//    query.addBindValue(email);
//    query.addBindValue(phonenumber);
//    query.exec();
//}


void DB_interaction::Stock_Unit_add(int quantity, QDate date_add)
{
    QSqlQuery query;
    cin >> quantity;
    date_add = QDate::currentDate();

    query.prepare("insert into Stock_Unit(date_add, quantity)"
                  "values(?, ?)");
    query.addBindValue(quantity);
    query.addBindValue(date_add);
    query.exec();

}

void DB_interaction::add_on_stock_trade_unit(int type_id, QString trademark, QString tradeunit)
{
   QSqlQuery query;
   cin >> type_id;
   cin >> trademark;
   cin >> tradeunit;
   query.prepare("insert into Stock_Trade_Unit(type, trademark, tradeunit)"
              "values(?, ?, ?)");
   query.addBindValue(type_id);
   query.addBindValue(trademark);
   query.addBindValue(tradeunit);
   query.exec();
}
/*void DB_interaction::add_on_stock_trade_unit(QString tradeunit)
{
    QSqlQuery query;


}*/

double DB_interaction::profit_from_table()
{

}
double DB_interaction::sum_of_order()
{
    //бля ну это пиздец вопросы по бд
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    QSqlDatabase crmDB;
    crmDB = QSqlDatabase::addDatabase("QMYSQL", "CRM_Stock_realisation");


    int a_type; //прототип add_on_stock идет до query.exec();
    QString a_trademark;
    QString a_tradeunit;
    QSqlQuery query;
    cin >> a_type;
    cin >> a_trademark;
    cin >> a_tradeunit;
    query.prepare("insert into Stock_Trade_Unit(type, trademark, tradeunit)"
               "values(?, ?, ?)");
    query.addBindValue(a_type);
    query.addBindValue(a_trademark);
    query.addBindValue(a_tradeunit);
    query.exec();

    return a.exec();
}
