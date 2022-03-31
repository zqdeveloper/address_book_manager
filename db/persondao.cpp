#include "persondao.h"
#include <QDir>
#include <QMap>

PersonDao::PersonDao()
{
    if (QSqlDatabase::contains("qt_sql_default_connection"))
    {
        database = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        database = QSqlDatabase::addDatabase("QSQLITE");
        QString path = QDir::homePath();
        qDebug()<<"homePath = "<<path;
        database.setDatabaseName(path+"/Desktop/person.db");
        database.setUserName("zhangqing");
        database.setPassword("zhangqing");

        if(!database.open()){
            qDebug("database open error");
        }
        QSqlQuery sql_query;
        QString create_sql = "CREATE TABLE IF NOT EXISTS person ( id  integer PRIMARY KEY AUTOINCREMENT, code varchar(32) not null UNIQUE,userName varchar ( 30 ),sex int,phoneNumber varchar ( 20 ),address text,mark text )";
        if(!sql_query.exec(create_sql)){
            qDebug() << sql_query.lastError();
        }
        database.close();
    }
}

//根据code批量删除联系人
int PersonDao::deletePerson(QStringList codes) {
    if(!database.open()){
        qDebug("database open error");
        return -1;
    }
    QString sql = "delete from person where code in (";
    for(int i=0,length = codes.size();i<length;i++){
        sql.append("?");
        if(i<length-1){
            sql.append(",");
        }
    }
    sql.append(")");
    qDebug()<<"sql= "<<sql<<";code = "<<codes;
    QSqlQuery sql_query;
    sql_query.prepare(sql);
    for(int i=0,length = codes.size();i<length;i++){
        sql_query.addBindValue(codes.at(i));
    }
    if(!sql_query.exec()){
        qDebug() << sql_query.lastError();
    }
    database.close();
    return codes.size();
}

//添加联系人
int PersonDao::insertPerson(Person* person) {
    if(!database.open()){
        qDebug("database open error");
        return -1;
    }
    QUuid code = QUuid::createUuid();
    person->setCode(code.toString().remove("{").remove("}").remove("-"));
    QString sql = "insert into person(code,userName,sex,phoneNumber,address,mark) values(?,?,?,?,?,?)";
    QSqlQuery sql_query;
    sql_query.prepare(sql);
    sql_query.addBindValue(person->getCode());
    sql_query.addBindValue(person->getUserName());
    sql_query.addBindValue(person->getSex());
    sql_query.addBindValue(person->getPhoneNumber());
    sql_query.addBindValue(person->getAddress());
    sql_query.addBindValue(person->getMark());
    if(!sql_query.exec()){
        qDebug() << sql_query.lastError();
    }
    database.close();
    return 1;
}

//修改联系人
int PersonDao::updatePerson(Person *person) {
    if(!database.open()){
        qDebug("database open error");
        return -1;
    }
    QString sql = "update person set userName = ?, sex = ?,phoneNumber = ? ,address = ?,mark = ? where code = ?";
    QSqlQuery sql_query;
    sql_query.prepare(sql);
    sql_query.addBindValue(person->getUserName());
    sql_query.addBindValue(person->getSex());
    sql_query.addBindValue(person->getPhoneNumber());
    sql_query.addBindValue(person->getAddress());
    sql_query.addBindValue(person->getMark());
    sql_query.addBindValue(person->getCode());
    if(!sql_query.exec())
    {
        qDebug()<<sql_query.lastError();
        return -1;
    }
    database.close();
    return 0;
}

//查询所有联系人
QList<Person*> PersonDao::selectAll() {
    QList<Person*> persons;
    if(!database.open()){
        qDebug("database open error");
        return persons;
    }
    QString sql = "select code,userName,sex,phoneNumber,address,mark,id from person order by id asc";
    QSqlQuery sql_query;
    if(!sql_query.exec(sql))
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {
        Person * person;
        while(sql_query.next())
        {
            QString code = sql_query.value(0).toString();
            QString userName = sql_query.value(1).toString();
            int sex = sql_query.value(2).toInt();
            QString phoneNumber = sql_query.value(3).toString();
            QString address = sql_query.value(4).toString();
            QString mark = sql_query.value(5).toString();
            int id = sql_query.value(6).toInt();
            person = new Person();
            person->setCode(code);
            person->setUserName(userName);
            person->setSex(sex);
            person->setPhoneNumber(phoneNumber);
            person->setAddress(address);
            person->setMark(mark);
            person->setId(id);
            persons.push_front(person);
        }
    }
    database.close();
    return persons;
}

//根据字段去重
QList<Person*> PersonDao::selectDistinctByColumn(QString column){
    QList<Person*> persons;
    if(!database.open()){
        qDebug("database open error");
        return persons;
    }
    QString sql = "select code,userName,sex,phoneNumber,address,mark,id from person group by "+column+" order by id asc";
    qDebug()<<"sql= "<<sql;
    QSqlQuery sql_query;
    if(!sql_query.exec(sql))
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {
        Person * person;
        while(sql_query.next())
        {
            QString code = sql_query.value(0).toString();
            QString userName = sql_query.value(1).toString();
            int sex = sql_query.value(2).toInt();
            QString phoneNumber = sql_query.value(3).toString();
            QString address = sql_query.value(4).toString();
            QString mark = sql_query.value(5).toString();
            int id = sql_query.value(6).toInt();
            person = new Person();
            person->setCode(code);
            person->setUserName(userName);
            person->setSex(sex);
            person->setPhoneNumber(phoneNumber);
            person->setAddress(address);
            person->setMark(mark);
            person->setId(id);
            persons.push_front(person);
        }
    }
    database.close();
    return persons;
}

//查询某个联系人
int PersonDao::selectByCode(Person* person, QString code){
    if(!database.open()){
        qDebug("database open error");
        return -1;
    }
    QString sql = "select code,userName,sex,phoneNumber,address,mark from person where code = '"+code+"'";
    QSqlQuery sql_query;
    if(!sql_query.exec(sql))
    {
        qDebug()<<sql_query.lastError();
        return -1;
    }
    else
    {
        if(sql_query.first()){
            QString code = sql_query.value("code").toString();
            QString userName = sql_query.value("userName").toString();
            int sex = sql_query.value("sex").toInt();
            QString phoneNumber = sql_query.value("phoneNumber").toString();
            QString address = sql_query.value("address").toString();
            QString mark = sql_query.value("mark").toString();

            person->setCode(code);
            person->setUserName(userName);
            person->setSex(sex);
            person->setPhoneNumber(phoneNumber);
            person->setAddress(address);
            person->setMark(mark);
            return 0;
        }
    }
    database.close();
    return-1;
}

//查询联系人
QList<Person*> PersonDao::selectAll(QMap<QString,QString> params) {
    QList<Person*> persons;
    if(!database.open()){
        qDebug("database open error");
        return persons;
    }
    QString sql = "select code,userName,sex,phoneNumber,address,mark,id from person";
    if(!params.isEmpty()){
        sql.append(" where ");
        QMapIterator<QString, QString> i(params);
        while (i.hasNext()) {
            i.next();
            sql.append(i.key());
            sql.append(" = ? ");
            sql.append(" and ");
        }
        sql.append(" 1=1");
    }
    sql.append(" order by id asc");
    qDebug()<<"sql = "<<sql;
    QSqlQuery sql_query;
    sql_query.prepare(sql);
    if(!params.isEmpty()){
        QMapIterator<QString, QString> i(params);
        while (i.hasNext()) {
         i.next();
         sql_query.addBindValue(i.value());
        }
    }
    if(!sql_query.exec())
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {
        Person * person;
        while(sql_query.next())
        {
            QString code = sql_query.value(0).toString();
            QString userName = sql_query.value(1).toString();
            int sex = sql_query.value(2).toInt();
            QString phoneNumber = sql_query.value(3).toString();
            QString address = sql_query.value(4).toString();
            QString mark = sql_query.value(5).toString();
            int id = sql_query.value(6).toInt();
            person = new Person();
            person->setCode(code);
            person->setUserName(userName);
            person->setSex(sex);
            person->setPhoneNumber(phoneNumber);
            person->setAddress(address);
            person->setMark(mark);
            person->setId(id);
            persons.push_front(person);
        }
    }
    database.close();
    return persons;
}

PersonDao::~PersonDao() {

}
