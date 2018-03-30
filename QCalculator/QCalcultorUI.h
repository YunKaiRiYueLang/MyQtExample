#ifndef _QCALCULTORUI_H_
#define _QCALCULTORUI_H_
#include<QLineEdit>
#include<QPushButton>
#include <QWidget>

class QCalcultorUI : public QWidget
{
  Q_OBJECT
private:
    QLineEdit* m_edit;
    QPushButton* m_buttons[20];
    QCalcultorUI();
    bool construct();
private slots:
    void onbtnclicked();
public:
    static QCalcultorUI* NewInstance();
    ~QCalcultorUI();
    void show();

};

#endif // QCALCULTORUI_H
