#ifndef PERSON_H
#define PERSON_H

#include <QObject>

class Person
{
public:
    Person();
    int getId();
    void setId(int Id);

    void setCode(QString code);
    QString getCode();

    QString getUserName();
    void setUserName(QString userName);

    void setSex(int sex);
    int getSex();

    QString getPhoneNumber();
    void setPhoneNumber(QString phoneNumber);

    QString getAddress();
    void setAddress(QString address);

    QString getMark();
    void setMark(QString mark);

private:
    int Id;
    //编号
    QString code;
    //姓名
    QString userName;
    //性别:0:男,1:女
    int sex;
    //联系电话
    QString phoneNumber;
    //地址
    QString address;
    //备注mark
    QString mark;
};

#endif // PERSON_H
