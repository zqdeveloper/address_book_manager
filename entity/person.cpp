#include "person.h"

Person::Person()
{
}
void Person::setId(int Id){
    this->Id = Id;
}
int Person::getId(){
    return this->Id;
}


QString Person::getCode()
{
    return this->code;
}
void Person::setCode(QString code){
    this->code = code;
}


void Person::setUserName(QString userName){
    this->userName = userName;
}
QString Person::getUserName(){
    return this->userName;
}

void Person::setSex(int sex){
    this->sex = sex;
}
int Person::getSex(){
    return this->sex;
}

void Person::setPhoneNumber(QString phoneNumber)
{
    this->phoneNumber = phoneNumber;
}
QString Person::getPhoneNumber(){
    return this->phoneNumber;
}


void Person::setAddress(QString address){
    this->address = address;
}
QString Person::getAddress(){
    return this->address;
}


void Person::setMark(QString mark){
    this->mark = mark;
}

QString Person::getMark(){
    return this->mark;
}


