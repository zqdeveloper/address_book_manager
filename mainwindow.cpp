#include "mainwindow.h"
#include "QHeaderView"
#include "window/createperson.h"
#include "db/persondao.h"
#include <QDebug>
#include "window/personinfo.h"
#include "utils/excelfileutils.h"
#include <QDir>
#include <QMap>

MainWindow::MainWindow(QWidget *parent): QWidget(parent)
{

    this->root = new QVBoxLayout();
    this->initMenu();
    this->root->addLayout(this->menu);
    this->initTable();
    this->root->addWidget(table);
    this->root->setStretchFactor(table,1);
    this->bindEvent();
    this->initData();
    setLayout(this->root);
}

//初始化操作面板
void MainWindow::initMenu()
{

    this->menu = new QVBoxLayout();
    QHBoxLayout * horizonation = new QHBoxLayout();

    addButton = new QPushButton("添加");
    addButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    addButton->resize(50,40);

    importButton = new QPushButton("导入");
    importButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    importButton->setMinimumSize(50,40);

    exportButton = new QPushButton("导出");
    exportButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    exportButton->setMinimumSize(50,40);

    this->distinct = new QPushButton("去重");

    horizonation->addWidget(addButton);
    horizonation->addWidget(importButton);
    horizonation->addWidget(exportButton);
    horizonation->addWidget(this->distinct);

    QSpacerItem *h = new QSpacerItem(20,20,QSizePolicy::Expanding , QSizePolicy::Ignored);
    horizonation->addSpacerItem(h);

    this->menu->addLayout(horizonation);
    this->menu->setStretchFactor(horizonation,1);

    QHBoxLayout *layout2 = new QHBoxLayout;
    this->menu->addLayout(layout2);
    this->menu->setStretchFactor(layout2,1);


    QLabel * userNameLabel = new QLabel("姓名");

    this->userName = new QLineEdit("");
    layout2->addWidget(userNameLabel);
    layout2->addWidget(this->userName);

    layout2->addSpacing(30);

    QLabel * phoneLabel = new QLabel("电话号码");
    layout2->addWidget(phoneLabel);
    this->phoneNumber = new QLineEdit("");
    layout2->addWidget(this->phoneNumber);

    selectButton = new QPushButton("查询");
   // selectButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Ignored);
    layout2->addWidget(selectButton);

    deleteButton = new QPushButton("删除");
    //deleteButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Ignored);
    layout2->addWidget(deleteButton);
}

//初始化数据面板
void MainWindow::initTable()
{
    table = new QTableWidget();
    table->setColumnCount(8);
    table->setRowCount(10);
    table->setGeometry(0,100,800,500);
    QStringList headers;
    headers<<""<<"编号"<<"姓名"<<"性别"<<"联系电话"<<"地址"<<"备注"<<"操作";
    table->setHorizontalHeaderLabels(headers);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    table->verticalHeader()->setHidden(true);
    //设置只能选择一行，不能选择多行
    table->setSelectionMode(QAbstractItemView::SingleSelection);
}

//绑定所有事件
void MainWindow::bindEvent() {
    //批量删除联系人
    connect(this->deleteButton,&QPushButton::clicked,this,&MainWindow::deletePerson);
    //导入外部联系人
    connect(this->importButton,&QPushButton::clicked,this,&MainWindow::importPerson);
    //添加新增联系人
    connect(this->addButton,&QPushButton::clicked,this,&MainWindow::saveOrupdate);
    //导出联系人到Excel
    connect(this->exportButton,&QPushButton::clicked,this,&MainWindow::exportPersons);
    //根据电话号码去重
    connect(this->distinct,&QPushButton::clicked,this,&MainWindow::distinctByPhone);
    //根据电话号码或者姓名进行查询
    connect(this->selectButton,&QPushButton::clicked,this,&MainWindow::selectPersons);
}

//删除联系人，单个或者批量
int MainWindow::deleteConstract(const QStringList codes){
    int result = QMessageBox::question(NULL, "删除确认", "确认要删除吗?", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    if(result==QMessageBox::Yes){
        PersonDao personDao;
        int status = personDao.deletePerson(codes);
        if(status!=-1){
            this->initData();
        }
    }
    return 0;
}

//批量删除联系人
void MainWindow::deletePerson() {
   QList<QString> codes;
   int rows = this->table->model()->rowCount();
   for(int i=0;i<rows;i++){
       QTableWidgetItem* checked = this->table->item(i,0);
       QTableWidgetItem * item = this->table->item(i,1);
       if(checked->checkState()==Qt::CheckState::Checked){
           QString code =item->text();
           codes<<code;
       }
   }
   if(codes.isEmpty()){
       QMessageBox::warning(this,"错误","请选择需要删除的联系人后再操作",QMessageBox::Button::Ok,QMessageBox::Button::Ok);
       return;
   }
   this->deleteConstract(codes);
}

//导入外部联系人
void MainWindow::importPerson() {
    QString path = QFileDialog::getOpenFileName(this,tr("Open File"), NULL, tr("*.xlsx"));
    qDebug()<<"fileName: "<<path;
    if (path.isEmpty()) {
        return;
    }
    PersonDao dao;
    ExcelFileUtils *excel = new ExcelFileUtils(path);
    QList<Person*> persons = excel->load();
    if(!persons.isEmpty()) {
        for(int i=0,length = persons.size();i<length;i++){
            Person * person = persons.at(i);
            dao.insertPerson(person);
        }
    }
    this->initData();
}

//导出联系人
void MainWindow::exportPersons(){

     QString path = QFileDialog::getSaveFileName(this,"选择保存位置",QDir::homePath(),"persons.xlsx");
     if(path.isEmpty()){
         return;
     }
     qDebug()<<path;
     PersonDao dao;
     QList<Person*> persons = dao.selectAll();
     ExcelFileUtils *excel = new ExcelFileUtils(path);
     excel->write(persons);
}

//新增联系人
void MainWindow::saveOrupdate() {
    CreatePerson *createPersonWindow = new CreatePerson(this);
    createPersonWindow->setModal(true);
    createPersonWindow->show();
    connect(createPersonWindow, &CreatePerson::refreshContacts,this, &MainWindow::refreshPersons);
}

//刷新数据
void MainWindow::refreshPersons(){
    this->initData();
}

//初始化数据
void MainWindow::initData(QString column)
{
    PersonDao personDao;
    QList<Person*> persons;
    if(column.isEmpty()){
       persons = personDao.selectAll();
    }
    else {
         persons = personDao.selectDistinctByColumn(column);
    }
    this->initPersons(persons);
}

void MainWindow::initPersons(QList<Person*> persons){
    this->table->setRowCount(persons.size());
    for(int i =persons.size()-1;i>=0;i--){
        Person * person = persons.at(i);
        QTableWidgetItem *check = new QTableWidgetItem();
        check->setCheckState(Qt::Unchecked);
        this->table->setItem(i,0, check);
        this->table->setItem(i,1, new QTableWidgetItem(person->getCode()));
        this->table->setItem(i,2, new QTableWidgetItem(person->getUserName()));
        this->table->setItem(i,3, new QTableWidgetItem(person->getSex()==1?"男":"女"));
        this->table->setItem(i,4, new QTableWidgetItem(person->getPhoneNumber()));
        this->table->setItem(i,5, new QTableWidgetItem(person->getAddress()));
        this->table->setItem(i,6, new QTableWidgetItem(person->getMark()));

        QPushButton *deleteItem  = new QPushButton("删除");
        deleteItem->setObjectName("delete");

        QPushButton *editItem  = new QPushButton("编辑");
        editItem->setObjectName("edit");

        QPushButton *details  = new QPushButton("详情");
        details->setObjectName("details");

        connect(deleteItem,&QPushButton::clicked,this,  &MainWindow::operationPerson);
        connect(editItem,&QPushButton::clicked,this, &MainWindow::operationPerson);
        connect(details,&QPushButton::clicked,this, &MainWindow::operationPerson);

        QWidget *widgget = new QWidget;

        QHBoxLayout * hboxLayout = new QHBoxLayout();
        hboxLayout->addWidget(deleteItem);
        hboxLayout->addWidget(editItem);
        hboxLayout->addWidget(details);
        widgget->setLayout(hboxLayout);
        this->table->setCellWidget(i,7,widgget);
        this->table->setRowHeight(i,40);
        this->table->setColumnWidth(7,120);
    }
}

//联系人操作
void MainWindow::operationPerson() {
     QPushButton *btn = (QPushButton*)sender();
     QString name = btn->objectName();

     QWidget *w_parent = (QWidget*)btn->parent();
     int x = w_parent->frameGeometry().x();
     int y = w_parent->frameGeometry().y();
     QModelIndex index = this->table->indexAt(QPoint(x,y));
     int row = index.row();
     //int col = index.column();
     QTableWidgetItem * widgetItem = this->table->item(row, 1);
     //编号
     QString code =  widgetItem->text();
     if(name == "edit") {
         CreatePerson *createPersonWindow = new CreatePerson(code,this);
         connect(createPersonWindow, &CreatePerson::refreshContacts,this, &MainWindow::refreshPersons);
         createPersonWindow->setModal(true);
         createPersonWindow->show();
     }
     if(name=="details"){
        PersonInfo *personInfo =new PersonInfo(code,this);
        personInfo->setModal(true);
        personInfo->show();
     }
     if(name=="delete"){
         QStringList codes;
         codes<<code;
        deleteConstract(codes);
     }
}

//根据电话号码去重
void MainWindow::distinctByPhone() {
    this->initData("phoneNumber");
}

//查询联系人
void MainWindow::selectPersons() {
    QString userName = this->userName->text();
    QString phoneNumber = this->phoneNumber->text();
    QMap<QString,QString> params;
    if(!userName.isEmpty()){
         params.insert("userName",userName);
    }
    if(!phoneNumber.isEmpty()){
         params.insert("phoneNumber",phoneNumber);
    }
    PersonDao personDao;
    QList<Person*> persons = personDao.selectAll(params);
    this->initPersons(persons);
}

//析构函数
MainWindow::~MainWindow()
{
    delete distinct;
    delete importButton;
    delete exportButton;
    delete selectButton;
    delete deleteButton;
    delete addButton;

    delete userName;
    delete phoneNumber;

    delete menu;
    delete  table;
    delete root;
}

