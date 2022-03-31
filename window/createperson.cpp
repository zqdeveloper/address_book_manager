#include "createperson.h"
#include <QMessageBox>

CreatePerson::CreatePerson(QWidget *parent): QDialog(parent),code("")
{
    this->setWindowTitle("添加信息");
    this->init();
    this->bindEvent();
    setLayout(this->root);
}

CreatePerson::CreatePerson(QString code,QWidget *parent):QDialog(parent),code(code){

    this->setWindowTitle("编辑信息");
    this->init();
    this->bindEvent();
    setLayout(this->root);
    this->initData();
}

void CreatePerson::init() {
    this->root = new QVBoxLayout();

    QHBoxLayout *top = new QHBoxLayout();

    QHBoxLayout *userNameLayout = new QHBoxLayout();
    QLabel *userNameLabel = new QLabel("        姓名");
    this->userName = new QLineEdit();

    userNameLayout->addWidget(userNameLabel);
    userNameLayout->addWidget(this->userName);
    userNameLayout->setStretchFactor(userName,1);

    QHBoxLayout *sexLayout = new QHBoxLayout();
    QLabel *sexLabel = new QLabel("性别");


    QButtonGroup *sexGroup = new QButtonGroup(sexLayout);
    this->woman = new QRadioButton("女");
    this->man = new QRadioButton("男");

    QHBoxLayout * sexButtonLayout = new QHBoxLayout();
    sexButtonLayout->addWidget(woman);
    sexButtonLayout->addWidget(man);


    sexGroup->addButton(woman,0);
    sexGroup->addButton(man,1);
    QSpacerItem *h1 = new QSpacerItem(0,0,QSizePolicy::Expanding, QSizePolicy::Ignored);
    sexButtonLayout->addSpacerItem(h1);

    sexLayout->addWidget(sexLabel);
    sexLayout->addLayout(sexButtonLayout);
    sexLayout->setStretchFactor(sexButtonLayout,1);

    top->addLayout(userNameLayout);
    top->addLayout(sexLayout);
    top->setStretchFactor(userNameLayout,1);
    top->setStretchFactor(sexLayout,1);


    this->root->addLayout(top);
    this->root->setStretchFactor(top, 1);

    QHBoxLayout *centerLayout = new QHBoxLayout();

    QHBoxLayout *phoneLayout = new QHBoxLayout();
    QLabel *phoneLabel = new QLabel("联系电话");
    phoneLayout->addWidget(phoneLabel);
    this->phone = new QLineEdit();
    phoneLayout->addWidget(phone);
    phoneLayout->setStretchFactor(phone,1);
    centerLayout->addLayout(phoneLayout);
    centerLayout->setStretchFactor(phoneLayout,1);

    QHBoxLayout *addressLayout = new QHBoxLayout();
    QLabel *addressLabel = new QLabel("地址");
    this->address = new QLineEdit();

    addressLayout->addWidget(addressLabel);
    addressLayout->addWidget(this->address);
    addressLayout->setStretchFactor(this->address,1);
    centerLayout->addLayout(addressLayout);
    centerLayout->setStretchFactor(addressLayout,1);

    this->root->addLayout(centerLayout);
    this->root->setStretchFactor(centerLayout,1);

    QHBoxLayout *markLayout = new QHBoxLayout();
    QLabel *markLabel = new QLabel("        备注");
    markLayout->addWidget(markLabel);

    this->mark = new QLineEdit();
    markLayout->addWidget(this->mark);
    markLayout->setStretchFactor(this->mark,1);

    this->root->addLayout(markLayout);
    this->root->setStretchFactor(markLayout,1);

    QHBoxLayout *bottom = new QHBoxLayout();

    QSpacerItem *h2= new QSpacerItem(0,0,QSizePolicy::Expanding,QSizePolicy::Ignored);
    bottom->addSpacerItem(h2);
    this->saveButton = new QPushButton("保存");
    this->cancelButton = new QPushButton("取消");

    bottom->addWidget(this->saveButton);
    bottom->addWidget(this->cancelButton);

    this->root->addLayout(bottom);
    this->root->setStretchFactor(bottom,1);
}

void CreatePerson::bindEvent(){
    //保存
    connect(this->saveButton,&QPushButton::clicked,this,&CreatePerson::save);
    //取消
    connect(this->cancelButton,&QPushButton::clicked,this,&CreatePerson::close);
}

//保存联系人
void CreatePerson::save(){
    Person * person = new Person();
    QString username = this->userName->text();
    QString phoneNumber = this->phone->text();
    QString mark = this->mark->text();
    QString address = this->address->text();
    if(username.isEmpty()){
        QMessageBox::warning(this,"错误","用户名不能为空",QMessageBox::Button::Ok,QMessageBox::Button::Ok);
        return;
    }
    if(phoneNumber.isEmpty()){
        QMessageBox::warning(this,"错误","电话号码不能为空",QMessageBox::Button::Ok,QMessageBox::Button::Ok);
        return;
    }
    if(address.isEmpty()){
        QMessageBox::warning(this,"错误","地址不能为空",QMessageBox::Button::Ok,QMessageBox::Button::Ok);
        return;
    }
    if(!this->woman->isChecked()&&!this->man->isChecked()){
        QMessageBox::warning(this,"错误","请选择用户性别",QMessageBox::Button::Ok,QMessageBox::Button::Ok);
        return;
    }
    person->setUserName(username);
    person->setAddress(address);
    person->setMark(mark);
    person->setPhoneNumber(phoneNumber);
    int sex = 1;
    if(this->woman->isChecked()){
        sex = 0;
    }
    if(this->man->isChecked()){
       sex = 1;
    }
    person->setSex(sex);
    PersonDao dao;
    QString title = "";
    QString content="";
    if(code.isEmpty())
    {
        dao.insertPerson(person);
        title = "保存成功";
        content = "成功保存一条记录";
    } else {
        person->setCode(code);
        dao.updatePerson(person);
        title = "修改成功";
        content = "成功修改一条记录";
    }
    int result = QMessageBox::information(this,title, content, QMessageBox::Yes, QMessageBox::Yes);
    if(result== QMessageBox::Yes){
        emit refreshContacts();
        this->close();
    }
}

//编辑信息赋初值
void CreatePerson::initData(){
    PersonDao personDao;
    Person person;
    if(code.isEmpty()){
        qDebug("code is empty");
        return;
    }
    int result = personDao.selectByCode(&person,code);
    if(result==0) {
        this->userName->setText(person.getUserName());
        this->phone->setText(person.getPhoneNumber());
        this->address->setText(person.getAddress());
        this->mark->setText(person.getMark());
        if(person.getSex()==1){
            this->man->setChecked(true);
            this->woman->setChecked(false);
        } else {
            this->man->setChecked(false);
            this->woman->setChecked(true);
        }
    } else {
        qDebug("记录为空");
    }
}

CreatePerson::~CreatePerson(){
    delete root;
    delete cancelButton;
    delete saveButton;
}
