#ifndef CREATEPERSON_H
#define CREATEPERSON_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QRadioButton>
#include <QButtonGroup>
#include <QPushButton>
#include "QSpacerItem"
#include "entity/person.h"
#include "db/persondao.h"
#include "QMessageBox"

class CreatePerson : public QDialog
{
    Q_OBJECT
public:
     CreatePerson(QWidget *parent = nullptr);
     CreatePerson(QString code, QWidget *parent = nullptr);
     void init();
     ~CreatePerson();
     void bindEvent();
     void initData();
private:
   QString code;
   QVBoxLayout *root;
   QLineEdit *userName;
   QLineEdit *phone;
   QLineEdit *address;
   QLineEdit *mark;
   QPushButton *saveButton;
   QPushButton *cancelButton;

   QRadioButton *woman;
   QRadioButton *man;
private slots:
    void save();
signals:
    void refreshContacts();
};

#endif // CREATEPERSON_H
