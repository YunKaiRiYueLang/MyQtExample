#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QPushButton>
#include<QPoint>
#include<QList>

class Widget : public QWidget
{
    Q_OBJECT

    enum
    {
        LINE,
        RECT,
        ELLIPSE
    };

    struct DrawParam
    {
        int type;
        Qt::PenStyle pen;
        QPoint begin;
        QPoint end;
    };

    QPushButton m_testBtn;
    QList<DrawParam> m_list;

public:
    Widget(QWidget *parent = 0);
    ~Widget();

protected slots:
    void onTestBtnClicked();
protected:
    void paintEvent(QPaintEvent*);
};

#endif // WIDGET_H
