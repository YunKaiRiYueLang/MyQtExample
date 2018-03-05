/* @program name:
 *
 * @system win7 Qt5.9.0
 * @brief
 * @author ���ӿ���
 * @data
 * @��� ���±������Ѿ����2017 11.28 �����Ժ󿴿���ʲô�޸İ汾���ϴ���git��github��
 */



/*
 * ����Ǳ�׼��qt��������Ĳ���д������Щ�鷳�ˣ�һ������������һ��������������Ϊ��
 * �����Ķ������ǲ�ζ��ˣ��ͻ�����Ķ��������ԡ�
 * �еĺ�������̣ܶ�û���ظ����ù��Ļ���û��Ҫ����һ��������̫�࣬�����װһ���డ��
 *
 *
 *
 * */



#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDateTime>
#include<QTextEdit>
#include<QLabel>
#include<QMenuBar>
#include<QIcon>
#include<QFileDialog>
#include<QMessageBox>
#include<QCloseEvent>
#include<QFile>
#include<QTextStream>
#include<QColorDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    textEdit = new QTextEdit();
    textEdit->setFont(QFont("����",15)); //����Ĭ�����壺���壬�����С
    setCentralWidget(textEdit);// �����ı�����Ϊ���ڵ����벿��


    textInfo = new QLabel();
    textInfo->setText("Redy");// Ĭ����ʾ���ݣ�
    statusBar()->addPermanentWidget(textInfo);

    fileMenu = new QMenu(this);//this,ָ��ǰ����
    editMenu = new QMenu(this);
    helpMenu = new QMenu(this);
    fileMenu = menuBar()->addMenu("File");
    editMenu = menuBar()->addMenu("Edit");
    helpMenu = menuBar()->addMenu("Help");

    newAct = new QAction(QIcon("Image/newFile"),"New",this);
    newAct->setShortcut((QKeySequence(Qt::CTRL+Qt::Key_N)));
    newAct->setStatusTip("New File");
    fileMenu->addAction(newAct);

//    QAction *quitAct; //�˳�
    openAct = new QAction(QIcon("Image/openFile"),"Open",this);//�������֣�ͼ�ꡣ�˴�û��ͼ���ļ�
    openAct->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_O));// ��ݼ�
    openAct->setStatusTip("Open file");//״̬����ʾ��Ϣ
    fileMenu->addAction(openAct);

    saveAct = new QAction(QIcon(""),"Save",this);
    saveAct->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_S));
    saveAct->setStatusTip("Save file");
    fileMenu->addAction(saveAct);

    saveasAct = new QAction(QIcon(""),"Save as",this);
    saveasAct->setShortcut(QKeySequence(Qt::CTRL+Qt::ALT+Qt::Key_S));
    saveasAct->setStatusTip("Save as another file");
    fileMenu->addAction(saveasAct);

    printAct = new QAction(QIcon(""),"Print",this);
    printAct->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_P));
    printAct->setStatusTip("Print file");
    fileMenu->addSeparator();
    fileMenu->addAction(printAct);

    quitAct = new QAction(QIcon(""),"Quit",this);
    quitAct->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_Q));
    quitAct->setStatusTip("Exit!");
    fileMenu->addSeparator();
    fileMenu->addAction(quitAct);

    aboutAct = new QAction(QIcon(""),"About",this);

    undo = new QAction(QIcon("Image/openFile"),"Undo",this);//�������֣�ͼ�ꡣ�˴�û��ͼ���ļ�
    undo->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_Z));// ��ݼ�
    undo->setStatusTip("undo");//״̬����ʾ��Ϣ
    editMenu->addAction(undo);

    redo = new QAction(QIcon("Image/openFile"),"Redo",this);//�������֣�ͼ�ꡣ�˴�û��ͼ���ļ�
   // redo->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_Z));// ��ݼ�
    redo->setStatusTip("undo");//״̬����ʾ��Ϣ
    editMenu->addAction(redo);

    cut = new QAction(QIcon("Image/openFile"),"Cut",this);//�������֣�ͼ�ꡣ�˴�û��ͼ���ļ�
    cut->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_X));// ��ݼ�
    cut->setStatusTip("cut");//״̬����ʾ��Ϣ
    editMenu->addAction(cut);

    copy = new QAction(QIcon("Image/openFile"),"Copy",this);//�������֣�ͼ�ꡣ�˴�û��ͼ���ļ�
    copy->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_C));// ��ݼ�
    copy->setStatusTip("copy");//״̬����ʾ��Ϣ
    editMenu->addAction(copy);

    paste = new QAction(QIcon("Image/openFile"),"Paste",this);//�������֣�ͼ�ꡣ�˴�û��ͼ���ļ�
    paste->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_V));// ��ݼ�
    paste->setStatusTip("paster");//״̬����ʾ��Ϣ
    editMenu->addAction(paste);

    fonttypeAct = new QAction(QIcon(""),"FONT",this);
    fonttypeAct->setStatusTip("zi ti she zhi ");
    ui->mainToolBar->addAction(fonttypeAct);

    fontcolorAct = new QAction(QIcon(""),"COLOR",this);
    fontcolorAct->setStatusTip("yanseshezhi");
    ui->mainToolBar->addAction(fontcolorAct);
   // no ��ݼ�
    aboutAct->setStatusTip("About author");
    helpMenu->addAction(aboutAct);

    connect(textEdit,SIGNAL(cursorPositionChanged()),this,SLOT(showTextInfo()));
    connect(aboutAct,SIGNAL(triggered(bool)),this,SLOT(aboutauthor()));
    connect(quitAct,SIGNAL(triggered(bool)),this,SLOT(exit_action()));// �Ƴ�
    connect(undo,SIGNAL(triggered()),this,SLOT(slotUndo()));
    connect(redo,SIGNAL(triggered()),this,SLOT(slotRedo()));
    connect(cut,SIGNAL(triggered()),this,SLOT(slotCut()));//cut
    connect(copy,SIGNAL(triggered()),this,SLOT(slotCopy()));//����
    connect(paste,SIGNAL(triggered()),this,SLOT(slotPaste()));//ճ��
    connect(openAct,SIGNAL(triggered(bool)),this,SLOT(slotOpen()));//open
    connect(newAct,SIGNAL(triggered()),this,SLOT(slotNew()));// NEW  ��ť
    connect(saveAct,SIGNAL(triggered()),this,SLOT(slotSave()));//save  ��ť
    connect(saveasAct,SIGNAL(triggered(bool)),this,SLOT(slotSave()));
    connect(fonttypeAct,SIGNAL(triggered()),this,SLOT(changeFontFamily()));// �������
    connect(fontcolorAct,SIGNAL(triggered()),this,SLOT(changeFontColor()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_D_triggered()
{
    QDateTime currenttime = QDateTime::currentDateTime();
    QString currtime  =currenttime.toString("dddd, d MMMM yy hh:mm:ss");
    textEdit->append(currtime);

}

void MainWindow::showTextInfo()
{
    QTextCursor textcursor = textEdit->textCursor();//������Ŷ���
    int line_num = textcursor.blockNumber();//������
    int colNum = textcursor.columnNumber();//����
    textInfo->setText(tr("Li:%1,Col:%2").arg(line_num+1).arg(colNum));// ��ʾ��label�ϣ��������㿪ʼ��
}
void MainWindow::exit_action()
{
    if(mabeSave()){
        qApp->closeAllWindows();//�ر����д��ڡ�
    }
}
void MainWindow::aboutauthor()
{
    QMessageBox::about(this,"About","This software was made by GongZiKaiMing!2017.11");
}

void MainWindow::slotOpen()
{
    if(mabeSave()){
       // QString filename = QFileDialog::getOpenFileName(this,tr("Open"),"",tr("Text Files(*.txt)"));
          QString filename = QFileDialog::getOpenFileName(this);
        if(!filename.isEmpty()){
            loadFile(filename);
        }
    }
}

bool MainWindow::slotSave()
{
    if(currentFile.isEmpty())
    {
        return slotSaveAs();
    }else{
        return saveFile(currentFile);
    }
}

void MainWindow::slotNew()
{
    if(mabeSave()){
        textEdit->clear();
        setFileName("");

    }
}

bool MainWindow::slotSaveAs()
{
    QString filename = QFileDialog::getSaveFileName(this,tr("save as "),"" ,tr("Text Files (*.txt)"));
    if(filename.isEmpty()){
        return false;
    }else{
        return saveFile(filename);
    }
}

void MainWindow::slotCut()
{
    textEdit->cut();
}


void MainWindow::slotCopy(){
    textEdit->copy();
}

void MainWindow::slotPaste(){
    textEdit->paste();
}

void MainWindow::slotRedo(){
    textEdit->redo();
}

void MainWindow::slotUndo(){
    textEdit->undo();
}

bool MainWindow::saveFile(QString &filename)
{
    QFile file(filename);
    if(!file.open(QFile::WriteOnly | QFile::Text)){
          QMessageBox::critical(this,
                                "critical",
                                "cannot write file"
                                );
          return false;
      }else{
        QTextStream out(&file);
        out<<textEdit->toPlainText();
        setFileName(filename);
        return true;
    }
}


//���������̫���G��
void MainWindow::setFileName(QString fileName){
    currentFile = fileName;
    textEdit->document()->setModified(false);
    this->setWindowModified(false);
    fileName.isEmpty()?
                this->setWindowFilePath("new.txt") :
                this->setWindowFilePath(fileName);
}

void MainWindow::loadFile(QString &filename)
{
    QFile file(filename);
    if(!file.open(QFile::ReadOnly|QFile::Text)){
        QMessageBox::critical(this,"critical","cannot read file");
    }else{
        QTextStream in(&file);
        textEdit->setText(in.readAll());
        setFileName(filename);
    }
}

void MainWindow::closeEvent(QCloseEvent *e)
{
    if(mabeSave()){
        e->accept();
    }else{
        e->ignore();
    }
}

void MainWindow::changeFontFamily()
{
    QFontDialog fontDlg;
    QFont font;
    bool isChanged;
    font = fontDlg.getFont(&isChanged);
    if(isChanged){
      textEdit->setFont(font);
    }
}

void MainWindow::changeFontColor()
{
    QColorDialog colorDlg;
    QColor color;
    QPalette palette = textEdit->palette();
    color = colorDlg.getColor(Qt::black);
    if(color.isValid())
{
        palette.setColor(QPalette::Text,color);// ������ɫ
        textEdit->setPalette(palette);
    }
}




bool MainWindow::mabeSave()
{
    if(textEdit->document()->isModified()){//�ж��Ƿ��޸�
        QMessageBox::StandardButton result;
        result  = QMessageBox::warning(this,"Warning","Do you want to save the file?",
                                       QMessageBox::Save|QMessageBox::Discard|QMessageBox::Cancel);
        if(result == QMessageBox::Cancel){// ȡ��
            return false;
        }
        if(result == QMessageBox::Save){//baocun
            return slotSave();
        }
        if(result == QMessageBox::Discard){//���ԣ���������
                   return true;
               }
    }else{
        return true;
    }
}


