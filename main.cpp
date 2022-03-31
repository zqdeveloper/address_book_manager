#include "mainwindow.h"

#include <QApplication>
/**
 * 1. 导入初始数据
 * 2. 显示信息
 * 3. 输入记录
 * 4. 删除记录
 * 5. 查询详情信息
 * 6. 编辑记录
 * 7. 去重
 * 8. 批量导出数据
 * 9. 退出
 * @brief main
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("通讯录管理程序");
    //w.setGeometry(100,400,800,600);
    //w.setMinimumSize(800,600);
    w.resize(800,600);
    w.show();
    return a.exec();
}
