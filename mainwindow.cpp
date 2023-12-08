#include "mainwindow.h"
#include "ui_mainwindow.h"

int num=0;
int num1=0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    resize(600,800);

    text->setParent(this);
    text->move(0,0);
    text->resize(200,50);
    text->setText("");//设置文本框

    but1->setParent(this);
    but1->resize(60,25);
    but1->move(200,13);
    but1->setText("开始搜索");//初始化按钮

    connect(but1,&QPushButton::clicked,text,[=](){
        data2=text->toPlainText();
        qDebug()<<data2<<endl;
        find(data2);
        int x=seletc();
        qDebug()<<"查找图片是否成功："<<x<<endl;
        if(x)
        {
            qDebug()<<"aaaa";
            but2->setParent(this);
            but2->resize(60,50);
            but2->move(300,350);
            but2->setText("下一张");
            but2->show();
            qDebug()<<"jjjj";
            connect(but2,&QPushButton::clicked,[=]()->void{
                num--;
                qDebug()<<"图片开始放置"<<endl;
                qDebug()<<num<<endl;
                putimage(num);
            });
            qDebug()<<num<<endl;

        }
        else
        {
            qDebug()<<"图片搜索失败"<<endl;
        }

    });



}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::seletc()//获取数据库查询信息
{
    QSqlDatabase::removeDatabase("qt_sql_default_connection");
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setHostName("localhost");
    db.setPort(3306);
    db.setDatabaseName("MYSQL"); //不是Database,记得别填错，应该是连接名字
    db.setUserName("root");
    db.setPassword("111111");

    bool ok = db.open();
    if (ok){
        QMessageBox::information(this, "infor", "数据库连接成功");

        QString keyword=data2;
        QString sql="select * from data where name like :keyword ";
        QSqlQuery query;

        query.prepare(sql);
        query.bindValue(":keyword","%"+keyword+"%");
        int ok1=query.exec();

        if(!ok1)
        {
                qDebug() << "获取数据失败"<<endl;
                QMessageBox::information(this, "infor", "获取数据失败");
                return false;
        }
        else
        {
            while(query.next())
                {
                    //取出当前记录中的字段
                    qDebug()<<query.value("name").toString();
                    //QMessageBox::information(this, "infor", "获取数据成功");
                    data[num]=query.value("name").toString();
                    qDebug()<<data[num]<<endl;
                    num++;
                    num1=num;
                }
            return true;
        }
        db.close();
    }
    else {
        QMessageBox::information(this, "infor", "数据库连接失败");
        return false;
    }
    return true;

}

void MainWindow::find(QString x)//从文本框拿到数据并插入到数据库中
{
    QSqlDatabase::removeDatabase("qt_sql_default_connection");
    QSqlDatabase db1 = QSqlDatabase::addDatabase("QODBC");
    db1.setHostName("localhost");
    db1.setPort(3306);
    db1.setDatabaseName("MYSQL"); //不是Database,记得别填错
    db1.setUserName("root");
    db1.setPassword("111111");

    QString key = x;
    bool ok = db1.open();
    if (ok){
        QMessageBox::information(this, "infor", "数据库链接成功");
        QSqlQuery query1(db1);

        QString sql=QString("insert into qtdata (message) values ('%1')").arg(key);
        int ok1=query1.exec(sql);

        if(!ok1)
        {
                qDebug() << "插入操作失败"<<endl;
                QMessageBox::information(this, "infor", "插入数据失败");
        }
        else
        {
                qDebug() << "插入操作成功"<<endl;
                QMessageBox::information(this, "infor", "已经成功插入数据！");
        }
    }
    db1.close();
}

void MainWindow::putimage(int x)
{
    QPixmap pixmp(data[x]);
    lab->setParent(this);
    lab->move(0,300);
    lab->setPixmap(pixmp);
    lab->setFixedSize(pixmp.size());
    lab->show();
}

void MainWindow::Picture()
{

}
