#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<QTextEdit>
#include<QLabel>
#include <QMainWindow>
#include<QMenu>
#include<QAction>
#include<QFontDialog>
#include<QString>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT



public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
  QString currentFile;

private slots:
  void on_action_D_triggered();//获取当前时间和日期
  void showTextInfo();



private:
  Ui::MainWindow *ui;
  QTextEdit *textEdit;
  QLabel *textInfo;
  QMenu *fileMenu;
  QMenu *editMenu;
  QMenu *helpMenu;

  QAction *newAct;
  QAction *openAct;
  QAction *saveAct;
  QAction *printAct; //打印
  QAction *quitAct; //退出
  QAction *saveasAct;

  QAction *aboutAct;

  QAction *undo;
  QAction *redo;
  QAction *cut;
  QAction *copy;
  QAction *paste;

  QAction *fonttypeAct;
  QAction *fontcolorAct;

private slots:
  void exit_action();
  void aboutauthor();
  bool mabeSave();
  void slotOpen();
  bool slotSave();
  void slotNew();
  bool slotSaveAs();

  void slotCut();
  void slotCopy();
  void slotPaste();
  void slotRedo();
  void slotUndo();
  bool saveFile(QString &filename);

  void setFileName(QString filename);
  void loadFile(QString &filename);

  void closeEvent(QCloseEvent *e);

  void changeFontFamily();
  void changeFontColor();


};

#endif // MAINWINDOW_H
