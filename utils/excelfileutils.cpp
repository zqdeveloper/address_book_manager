#include "excelfileutils.h"

ExcelFileUtils::ExcelFileUtils(QString path):path(path){

}

int ExcelFileUtils::write(QList<Person*> persons){
     QXlsx::Document xlsxW;
     xlsxW.write("A1","姓名");
     xlsxW.write("B1","编号");
     xlsxW.write("C1","电话号码");
     xlsxW.write("D1","地址");
     xlsxW.write("E1","性别");
     xlsxW.write("F1","备注");
     xlsxW.write("G1","Id");
     for(int i=0,length = persons.size();i<length;i++)
     {
         QString row = QString::number(i+2);
         Person * person = persons.at(i);
         xlsxW.write("A"+row, person->getUserName());
         xlsxW.write("B"+row, person->getCode());
         xlsxW.write("C"+row, person->getPhoneNumber());
         xlsxW.write("D"+row, person->getAddress());
         xlsxW.write("E"+row, person->getSex()==1?"男":"女");
         xlsxW.write("F"+row, person->getMark());
         xlsxW.write("G"+row, QString::number(person->getId()));
     }
     if ( xlsxW.saveAs(this->path))
     {
         qDebug() << "[debug] success to write xlsx file";
         return 0;
     }
     return -1;
}


QList<Person*> ExcelFileUtils::load() {
    QList<Person*> persons;
    QXlsx::Document xlsxR(this->path);
    if ( xlsxR.load())
    {
        qDebug() << "[debug] success to load xlsx file.";
        Person * person;
        for(int row = 2;row<=xlsxR.dimension().rowCount();row++) {
            person = new Person();
            for(int col = 1; col<=xlsxR.dimension().columnCount();col++){
                QXlsx::Cell* cell = xlsxR.cellAt(row, col); // get cell pointer.
                QVariant var = cell->readValue();
                switch(col){
                case 1:
                    person->setUserName(var.value<QString>());
                    break;
                case 2:
                    person->setCode(var.value<QString>());
                    break;
                case 3:
                    person->setPhoneNumber(var.value<QString>());
                    break;
                case 4:
                     person->setAddress(var.value<QString>());
                    break;
                case 5:
                    person->setSex(var.value<QString>()=="男"?1:0);
                    break;
                case 6:
                     person->setMark(var.value<QString>());
                    break;
                }
            }
            persons.append(person);
        }
    }
    else
    {
        qDebug() << "[debug][error] failed to load xlsx file.";
    }
    return persons;
}
