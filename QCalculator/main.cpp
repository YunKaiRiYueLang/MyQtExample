#include <QApplication>
#include<QCalcultorUI.h>
// 生成界面的代码放到main函数使main函数功能不唯一了。一个函数一般只对应一个功能原则
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCalcultorUI *cal=QCalcultorUI::NewInstance();
    int ret=-1;
    if(cal!=NULL)
    {
        cal->show();
        ret=a.exec();
        delete cal;
    }

    return ret;
}
