#include "personinfo.h"
#include "entity/person.h"
#include "db/persondao.h"
#include <QDebug>

PersonInfo::PersonInfo(QString code,QWidget *parent): QDialog(parent),code(code)
{
    this->setWindowTitle("详情");
    this->initUI();
    this->initData();
}

void PersonInfo::initUI(){

    this->root = new QVBoxLayout();

    QHBoxLayout * codeLayout = new QHBoxLayout();
    QLabel *codeLabel = new QLabel("编号");
    codeLayout->addWidget(codeLabel);
    this->codeValue = new QLabel();
    codeLayout->addWidget(codeValue);
    QSpacerItem *line = new QSpacerItem(0,0,QSizePolicy::Expanding,  QSizePolicy::Ignored);
    codeLayout->addSpacerItem(line);

     QHBoxLayout * nameAndSexLayout = new QHBoxLayout();


     QHBoxLayout * nameLayout = new QHBoxLayout();
     QLabel *nameLabel = new QLabel("姓名");
     this->userName = new QLabel();

     nameLayout->addWidget(nameLabel);
     nameLayout->addWidget(this->userName);
     nameLayout->addSpacerItem(line);


     QHBoxLayout * sexLayout = new QHBoxLayout();

     QLabel *sexLabel = new QLabel("性别");
     this->sex = new QLabel();


     sexLayout->addWidget(sexLabel);
     sexLayout->addWidget(this->sex);
     sexLayout->addSpacerItem(line);


     nameAndSexLayout->addLayout(nameLayout);
     nameAndSexLayout->addLayout(sexLayout);


     QHBoxLayout * phonneLayout = new QHBoxLayout();

     QLabel *phoneLabel = new QLabel("联系电话");
     this->phone = new QLabel();
     phonneLayout->addWidget(phoneLabel);
     phonneLayout->addWidget(this->phone);
     phonneLayout->addSpacerItem(line);


     QHBoxLayout *addressLayout = new QHBoxLayout();

     QLabel *addressLabel = new QLabel("地址");
     this->address = new QLabel();
     addressLayout->addWidget(addressLabel);
     addressLayout->addWidget(this->address);
     addressLayout->addSpacerItem(line);

     QHBoxLayout *markLayout = new QHBoxLayout();

     QLabel *markLabel = new QLabel("地址");
     this->mark = new QLabel();
     markLayout->addWidget(markLabel);
     markLayout->addWidget(this->mark);
     markLayout->addSpacerItem(line);


     QHBoxLayout *closeLayout   = new QHBoxLayout();
     closeLayout->addSpacerItem(line);

     QPushButton *close = new QPushButton("关闭");
     closeLayout->addWidget(close);

     connect(close,&QPushButton::clicked,this,&PersonInfo::close);


    this->root->addLayout(codeLayout);
    this->root->addLayout(nameAndSexLayout);
    this->root->addLayout(phonneLayout);
    this->root->addLayout(addressLayout);
    this->root->addLayout(markLayout);
    this->root->addSpacing(40);
    this->root->addLayout(closeLayout);
    this->setLayout(this->root);
}

void PersonInfo::initData(){
    Person person;
    PersonDao personDao;
    int result = personDao.selectByCode(&person,this->code);
    if(result!=0){
        qDebug("记录不存在");
        return;
    }
    this->codeValue->setText(person.getCode());
    this->userName->setText(person.getUserName());
    this->sex->setText(person.getSex()==1?"男":"女");
    this->phone->setText(person.getPhoneNumber());
    this->address->setText(person.getAddress());
    this->mark->setText(person.getMark());
}


PersonInfo::~PersonInfo(){
    delete root;
}
