#include "QCalcultorUI.h"
#include<QDebug>
// 二阶构造 构造
QCalcultorUI::QCalcultorUI() : QWidget(NULL,Qt::WindowCloseButtonHint)
{
}

bool QCalcultorUI::construct()
{
    bool ret=true;
   const char*btnText[20]=
    {
        "7","8","9","+","(",
        "4","5","6","-","0",
        "1","2","3","*","<-",
        "0",".","=","/","C",
    };
    m_edit=new QLineEdit(this);
    if(m_edit!=NULL)
    {
        m_edit->move(10,10);
        m_edit->resize(240,30);
        m_edit->setReadOnly(true);
        m_edit->setAlignment(Qt::AlignRight);
    }
    else{
        ret =false;
    }
    for(int i =0;i<4&&ret;i++)
    {
        for(int j=0;j<5&&ret;j++)
        {
            m_buttons[i*5+j]=new QPushButton(this);
            if(m_buttons[i*5+j]!=NULL)
            {
            m_buttons[i*5+j]->resize(40,40);
            m_buttons[i*5+j]->move(10+(10+40)*j,50+(40+10)*i);
            m_buttons[i*5+j]->setText(btnText[i*5+j]);
            connect(m_buttons[i*5+j],SIGNAL(clicked()),this,SLOT(onbtnclicked()));
            }
        }
    }

    return ret;
}


void QCalcultorUI::show()
{
    QWidget::show();
    setFixedSize(width(),height());
}


 QCalcultorUI* QCalcultorUI::NewInstance()
{
    QCalcultorUI * ret=new QCalcultorUI();
    if((ret==NULL)||!ret->construct())
    {
        delete ret;
        ret=NULL;
    }

    return ret;
}

QCalcultorUI::~QCalcultorUI()
{

}

void QCalcultorUI::onbtnclicked()
{
  QPushButton *btn=(QPushButton*)sender();
  QString clicktext=btn->text();
  if(clicktext=="<-")
  {
    QString text=m_edit->text();
    if(text.length()>0)
    {
      text.remove(text.length()-1,1);
      m_edit->setText(text);
    }
  }else if(clicktext=="C")
  {
    m_edit->setText("");
  }else if(clicktext=="=")
  {

  }else{
    m_edit->setText(m_edit->text()+clicktext);
  }


}
