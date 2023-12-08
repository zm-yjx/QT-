#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QDebug>
#include<QSqlDatabase>
#include<QMessageBox>
#include<QSqlQuery>
#include<QString>
#include<QDir>
#include<QTextEdit>
#include<QPushButton>
#include<QWidget>
#include<QLabel>
#include<QSqlRecord>
#include<QVBoxLayout>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    bool seletc();
    void find(QString x);
    void putimage(int x);
    void Picture();
    ~MainWindow();

private:
    QString data[50];//记录图片路径
    QString data2;//记录搜索内容
    QTextEdit * text=new QTextEdit;//搜索文本框，用于采集数据
    QPushButton *but1=new QPushButton;//按键一用于触发信号和槽
    QPushButton *but2=new QPushButton;//按键二用于查询下一张图片
    QLabel * lab=new QLabel;//从初始化一个label控件来放置图片
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
