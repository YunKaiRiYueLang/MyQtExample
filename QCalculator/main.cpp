#include <QApplication>
#include<QCalcultorUI.h>
// ���ɽ���Ĵ���ŵ�main����ʹmain�������ܲ�Ψһ�ˡ�һ������һ��ֻ��Ӧһ������ԭ��
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
