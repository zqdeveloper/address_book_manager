#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QDebug>
#include "QTableWidget"
#include "QHBoxLayout"
#include "QPushButton"
#include "QVBoxLayout"
#include "QLineEdit"
#include "QTableWidget"
#include "QMessageBox"
#include "qfiledialog.h"
#include "entity/person.h"

class MainWindow : public QWidget
{

public:
    MainWindow(QWidget *parent = nullptr);
    //初始化按钮
    void initMenu();
    //初始化tableWidget
    void initTable();
    //删除联系人
    int deleteConstract(const QStringList personCodes);
    //绑定各种事件
    void bindEvent();
    //加载数据库中的数据
    void initData(QString column="");
    //设置联系人数据
    void initPersons(QList<Person*> persons);
    ~MainWindow();
private:
    //承载数据的table
     QTableWidget *table;
     //系列操作按钮区域
     QVBoxLayout *menu;
     //根面板
     QVBoxLayout *root;
     //从外部导入联系人
     QPushButton *importButton;
     //导出联系人按钮
     QPushButton *exportButton;
     //添加新的联系人按钮
     QPushButton *addButton;
     //查询联系人按钮
     QPushButton *selectButton;
     //批量删除联系人按钮
     QPushButton *deleteButton;

     //用户名
     QLineEdit * userName;
     //电话号码
     QLineEdit * phoneNumber;
     //去重按钮
     QPushButton * distinct;
  private slots:
     //批量删除联系人
     void deletePerson();
     //导入外部联系人
     void importPerson();
     //添加新增联系人
     void saveOrupdate();
     //导出联系人到Excel
     void exportPersons();
     //根据电话号码去重
     void distinctByPhone();
     //查询联系人
     void selectPersons();
     //联系人操作：1.编辑，2.删除，3.详情
     void operationPerson();
     //刷新联系人数据
     void refreshPersons();
};
#endif
