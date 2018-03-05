/* @program name:
 *
 * @system win7 Qt5.9.0
 * @brief
 * @author 公子开明
 * @data
 * @相关 记事本功能已经完成2017 11.28 可以以后看看有什么修改版本，上传至git和github。
 */



/*
 * 这个是标准的qt的例子里的步骤写法。有些麻烦了，一个函数包含另一个函数，本来是为了
 * 方便阅读，但是层次多了，就会干扰阅读的流畅性。
 * 有的函数本身很短，没有重复调用过的话，没必要另起一个函数，太多，不如封装一个类啊。
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
    textEdit->setFont(QFont("宋体",15)); //设置默认字体：字体，字体大小
    setCentralWidget(textEdit);// 设置文本区域为窗口的中央部件


    textInfo = new QLabel();
    textInfo->setText("Redy");// 默认显示内容；
    statusBar()->addPermanentWidget(textInfo);

    fileMenu = new QMenu(this);//this,指当前窗口
    editMenu = new QMenu(this);
    helpMenu = new QMenu(this);
    fileMenu = menuBar()->addMenu("File");
    editMenu = menuBar()->addMenu("Edit");
    helpMenu = menuBar()->addMenu("Help");

    newAct = new QAction(QIcon("Image/newFile"),"New",this);
    newAct->setShortcut((QKeySequence(Qt::CTRL+Qt::Key_N)));
    newAct->setStatusTip("New File");
    fileMenu->addAction(newAct);

//    QAction *quitAct; //退出
    openAct = new QAction(QIcon("Image/openFile"),"Open",this);//设置名字，图标。此处没有图标文件
    openAct->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_O));// 快捷键
    openAct->setStatusTip("Open file");//状态栏提示信息
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

    undo = new QAction(QIcon("Image/openFile"),"Undo",this);//设置名字，图标。此处没有图标文件
    undo->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_Z));// 快捷键
    undo->setStatusTip("undo");//状态栏提示信息
    editMenu->addAction(undo);

    redo = new QAction(QIcon("Image/openFile"),"Redo",this);//设置名字，图标。此处没有图标文件
   // redo->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_Z));// 快捷键
    redo->setStatusTip("undo");//状态栏提示信息
    editMenu->addAction(redo);

    cut = new QAction(QIcon("Image/openFile"),"Cut",this);//设置名字，图标。此处没有图标文件
    cut->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_X));// 快捷键
    cut->setStatusTip("cut");//状态栏提示信息
    editMenu->addAction(cut);

    copy = new QAction(QIcon("Image/openFile"),"Copy",this);//设置名字，图标。此处没有图标文件
    copy->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_C));// 快捷键
    copy->setStatusTip("copy");//状态栏提示信息
    editMenu->addAction(copy);

    paste = new QAction(QIcon("Image/openFile"),"Paste",this);//设置名字，图标。此处没有图标文件
    paste->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_V));// 快捷键
    paste->setStatusTip("paster");//状态栏提示信息
    editMenu->addAction(paste);

    fonttypeAct = new QAction(QIcon(""),"FONT",this);
    fonttypeAct->setStatusTip("zi ti she zhi ");
    ui->mainToolBar->addAction(fonttypeAct);

    fontcolorAct = new QAction(QIcon(""),"COLOR",this);
    fontcolorAct->setStatusTip("yanseshezhi");
    ui->mainToolBar->addAction(fontcolorAct);
   // no 快捷键
    aboutAct->setStatusTip("About author");
    helpMenu->addAction(aboutAct);

    connect(textEdit,SIGNAL(cursorPositionChanged()),this,SLOT(showTextInfo()));
    connect(aboutAct,SIGNAL(triggered(bool)),this,SLOT(aboutauthor()));
    connect(quitAct,SIGNAL(triggered(bool)),this,SLOT(exit_action()));// 推出
    connect(undo,SIGNAL(triggered()),this,SLOT(slotUndo()));
    connect(redo,SIGNAL(triggered()),this,SLOT(slotRedo()));
    connect(cut,SIGNAL(triggered()),this,SLOT(slotCut()));//cut
    connect(copy,SIGNAL(triggered()),this,SLOT(slotCopy()));//复制
    connect(paste,SIGNAL(triggered()),this,SLOT(slotPaste()));//粘贴
    connect(openAct,SIGNAL(triggered(bool)),this,SLOT(slotOpen()));//open
    connect(newAct,SIGNAL(triggered()),this,SLOT(slotNew()));// NEW  按钮
    connect(saveAct,SIGNAL(triggered()),this,SLOT(slotSave()));//save  按钮
    connect(saveasAct,SIGNAL(triggered(bool)),this,SLOT(slotSave()));
    connect(fonttypeAct,SIGNAL(triggered()),this,SLOT(changeFontFamily()));// 字体相关
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
    QTextCursor textcursor = textEdit->textCursor();//获得鼠标哦光标
    int line_num = textcursor.blockNumber();//行数；
    int colNum = textcursor.columnNumber();//列数
    textInfo->setText(tr("Li:%1,Col:%2").arg(line_num+1).arg(colNum));// 显示在label上，行数从零开始的
}
void MainWindow::exit_action()
{
    if(mabeSave()){
        qApp->closeAllWindows();//关闭所有窗口。
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


//这个函数不太懂欸。
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
        palette.setColor(QPalette::Text,color);// 设置颜色
        textEdit->setPalette(palette);
    }
}




bool MainWindow::mabeSave()
{
    if(textEdit->document()->isModified()){//判断是否被修改
        QMessageBox::StandardButton result;
        result  = QMessageBox::warning(this,"Warning","Do you want to save the file?",
                                       QMessageBox::Save|QMessageBox::Discard|QMessageBox::Cancel);
        if(result == QMessageBox::Cancel){// 取消
            return false;
        }
        if(result == QMessageBox::Save){//baocun
            return slotSave();
        }
        if(result == QMessageBox::Discard){//忽略，即不保存
                   return true;
               }
    }else{
        return true;
    }
}


