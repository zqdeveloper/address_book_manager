#ifndef PERSONDAO_H
#define PERSONDAO_H

#include <QObject>
#include <QDebug>
#include "entity/person.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QList>
#include <QUuid>

class PersonDao
{
public:
    PersonDao();
    int insertPerson(Person* person);
    int updatePerson(Person* person);
    int deletePerson(QStringList code);
    int selectByCode(Person* person, QString code);
    QList<Person*> selectAll();
    QList<Person*> selectDistinctByColumn(QString column);
    QList<Person*> selectAll(QMap<QString,QString> params);
    QSqlDatabase database;
    ~PersonDao();
};

#endif // PERSONDAO_H
