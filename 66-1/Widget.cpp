#include "Widget.h"
#include<QPainter>
#include<QPoint>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    m_testBtn.setParent(this);//*表示该按钮的父组件市当前widget
    m_testBtn.move(400,300);//*位于400 300处
    m_testBtn.resize(70,30);//*宽70高30
    m_testBtn.setText("Test");//*设置文本
    resize(500,350);//*设置该widget大小
    connect(&m_testBtn,SIGNAL(clicked()),this,SLOT(onTestBtnClicked()));
}

Widget::~Widget()
{

}

void Widget::onTestBtnClicked()
{
    DrawParam dp=
    {
        qrand()%3,
        static_cast<Qt::PenStyle>(qrand()%5+1),
        QPoint(qrand()%400,qrand()%300),
        QPoint(qrand()%400,qrand()%300)
    };
    m_list.append(dp);
    update();


}
void Widget::paintEvent(QPaintEvent*)
{
    QPainter painter;
    painter.begin(this);//*再当前widget中绘图
    painter.drawLine(QPoint(30,30),QPoint(200,200));
    for(int i=0;i<m_list.count();i++)
    {
        int x=(m_list[i].begin.x()<m_list[i].end.x())?m_list[i].begin.x():m_list[i].end.x();
        int y=(m_list[i].begin.y()<m_list[i].end.y())?m_list[i].begin.y():m_list[i].end.y();
        int w=qAbs(m_list[i].begin.x()-m_list[i].end.x())+1;
        int h=qAbs(m_list[i].begin.y()-m_list[i].end.y())+1;

        painter.setPen(m_list[i].pen);
        switch (m_list[i].type) {
        case LINE:
            painter.drawLine(m_list[i].begin,m_list[i].end);
        case RECT:
            painter.drawRect(x,y,w,h);
        case ELLIPSE:
            painter.drawEllipse(x,y,w,h);
        default:
            break;
        }
    }


    painter.end();
}
