#ifndef PERSONINFO_H
#define PERSONINFO_H

#include <QWidget>
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QSpacerItem>
#include <QPushButton>

class PersonInfo : public QDialog
{
public:
     PersonInfo(QString code, QWidget *parent = nullptr);
     void initUI();
     void initData();
     ~PersonInfo();
private:
    QVBoxLayout * root;
    QString code;
    QLabel * codeValue;
    QLabel * userName;
    QLabel * sex;
    QLabel * phone;
    QLabel * address;
    QLabel * mark;
signals:

};
#endif // PERSONINFO_H
