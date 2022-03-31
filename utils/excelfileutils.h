#ifndef EXCELFILEUTILS_H
#define EXCELFILEUTILS_H

#include <QObject>
#include "xlsxdocument.h"
#include "xlsxchartsheet.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"
#include "entity/person.h"

class ExcelFileUtils
{
public:
    ExcelFileUtils(QString path);
    int write(QList<Person*> persons);
    QList<Person*> load();
    ~ExcelFileUtils();
private:
    QString path;
signals:

};

#endif // EXCELFILEUTILS_H
