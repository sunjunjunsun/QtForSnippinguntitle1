#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QColor>
#include <QDateTime>
#include <QDir>
#include <QScreen>
#include <QGuiApplication>
#include <QEventLoop>
#include <QTimer>
#include<QApplication>
#include <QDesktopWidget>
#include <QFile>
#include <QtXml>
#include <QCoreApplication>
#include <QString>
#include <QTime>
#include <QMessageBox>
#include <QMenu>
#include <QAction>
#include <QCursor>
#include <QClipboard>
#include <QTimerEvent>
#include <QDesktopServices>

#define TIMER_TIMEOUT   (60*1000)
//宏常量



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    watcher = new QFileSystemWatcher(this);
    QObject::connect(watcher, SIGNAL(fileChanged(QString)),this, SLOT(onFileChanged(QString)));
    ui->lineEdit->setText("V810-8088S2");
    ui->lineEdit_2->setText("R12");
    ui->lineEdit_3->setText("BT104902034");
    QObject::connect(ui->lineEdit_6,SIGNAL(returnPressed()),this,SLOT(on_pushButton_5_clicked()));  //支持回车补资料
    QObject::connect(ui->lineEdit_search,SIGNAL(returnPressed()),this,SLOT(on_pushButton_4_clicked()));
    QObject::connect(ui->lineEdit_SnL22,SIGNAL(returnPressed()),this,SLOT(on_pushButton_BTN_L22_clicked()));
    QObject::connect(ui->lineEdit_SnL12,SIGNAL(returnPressed()),this,SLOT(on_pushButton_BTN_L12_clicked()));
    QObject::connect(ui->lineEdit_SnK12,SIGNAL(returnPressed()),this,SLOT(on_pushButton_BTN_K12_clicked()));
    QObject::connect(ui->lineEdit_SnK22,SIGNAL(returnPressed()),this,SLOT(on_pushButton_BTN_K22_clicked()));
    ui->radioButton->setChecked(true);
    ui->radioButton_3->setChecked(true);
    //ui->listWidget_2->addItem("BT104902038_K12_V810-8085S2");
    //ui->listWidget_2->addItem("1PL21312312_Q12_V810-3325S2EX");
    //ui->listWidget_2->addItem("DTH1231221312312_P12_V810-3328S2EX");
   // ui->listWidget_2->addItem("QSSA1231243242_J12_V810-3327S2EX");
    //   ui->listWidget->setBackgroundRole(QPalette(QColor(241,197,129)));
    ui->listWidget->setAlternatingRowColors(true); // 隔行变色
    const QColor color = QColor(241,197,129);
    ui->listWidget->setPalette(QPalette(color)); // 设置隔行变色的颜色  gray灰色
   // ui->textEdit_2->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
   // ui->textEdit_2->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    //ui->textEdit_2->verticalScrollBar()->setValue(ui->textEdit_2->verticalScrollBar()->maximumHeight());
    //ui->textEdit->setLineWrapMode(QTextEdit::NoWrap);
    ui->listWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    QString pathdemo1="C:\\sn\\records";
    QDir dirs(pathdemo1);
    if(!dirs.exists())
    {
        dirs.mkpath(pathdemo1);
    }
    QString dateText = QDateTime::currentDateTime().toString("yyyyMMdd");
    QString fileWatcher=pathdemo1 + "\\" + dateText + ".txt";
    QFile fileWa(fileWatcher);
    if(!fileWa.exists(fileWatcher))
    {
       fileWa.open(QIODevice::WriteOnly|QIODevice::Text);
    }
    fileWatcherPath=fileWatcher;
   // qDebug() << fileWatcher;
    fileWa.close();
    watcher->addPath(fileWatcherPath);
     //watcher->addPath("C:\\SN\\records\\20201220.txt");
    // m_nTimerID=this->startTimer(TIMER_TIMEOUT); //定时器，每60s检查一次监控的文件路径是否按日期来的
    this->setWindowTitle("截图自动Qt版V1.0.0[20201222]");
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::timerEvent(QTimerEvent *event)
{

   /*
    * if(event->timerId()==m_nTimerID){
        handleTimeout();
    }
    */

}

void MainWindow::handleTimeout()
{
   // qDebug() << "我是60s是执行的一次函数";
   // killTimer(m_nTimerID);
    /*QString pathTime = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    QString pathTime2 = QDateTime::currentDateTime().toString("yyyy-MM-dd");
    QString paths= QString("%1 23:59:59").arg(pathTime2);
    QDateTime nowTime = QDateTime::fromString(pathTime,"yyyy-MM-dd HH:mm:ss");
    QDateTime fixedTime = QDateTime::fromString(paths,"yyyy-MM-dd HH:mm:ss");
    uint nowTime_s = nowTime.toTime_t();
    uint fixedTime_s = fixedTime.toTime_t();
    int c = fixedTime_s -nowTime_s;
    if(c>0)
    {
        //当天的文件夹
    }
    if(c<0){
      //创建第二天的文件夹,并存放相应的文件
       QString datePath = QDateTime::currentDateTime().addDays(+1).toString("MMdd");

    }*/
 /*
  * QString demo1 = QDateTime::currentDateTime().toString("yyyyMMdd");
  fileWatcherPath = "C:\\SN\\records\\"+demo1 + ".txt";
  watcher->addPath(fileWatcherPath);*/


}


void MainWindow::onFileChanged(const QString &path)
{
    //文件创建的时候执行的函数
    QFile file(path);
    QString lastLine;
    if (file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
       // QString text(file.readAll());
        //ui->textEdit->setText(text);
        //QFile fp("C:\\SN\\records\\20201220.txt");
        QFile fp(fileWatcherPath);
        fp.open(QIODevice::ReadOnly);
        int len = fp.size();
        int i = 3;
        fp.seek(len-i);
        while (!QString(fp.readLine()).compare("\n") == 0)
        {
            i++;
            fp.seek(len - i);
        }
        lastLine=fp.readLine().trimmed();
        //lastLine.split('_')[0].toUpper();
        //   ui->lineEdit_2->setText( lastLine.split('_')[1].toUpper());
        //     ui->lineEdit_3>setText( lastLine.split('_')[0].toUpper());
        fp.close();
        //   int data2= lastLine.split(",")[1].toInt();
        //     qDebug() << lastLine;
        file.close();
    }
    ui->lineEdit->setText(lastLine.split('_')[2].toUpper());
    ui->lineEdit_2->setText(lastLine.split('_')[1].toUpper());
    ui->lineEdit_3->setText(lastLine.split('_')[0].toUpper());
    //listWidget_2 添加的是正序Sn的排列数据
    ui->listWidget_2->addItem(lastLine);
   //  ui->listWidget->sortItems(Qt::DescendingOrder);
    QStringList list;
     //用之前清空一下，防止内存泄漏
    list.clear();
    int row  = 0;
    QString line;
    while(row < (ui->listWidget_2->count()))
    {
        line = ui->listWidget_2->item(row)->text();
        list<<line;
        row++;
    }
     QStringListIterator iterator(list);
     //遍历到末尾
     while(iterator.hasNext())
     {
         iterator.next();
     }
     QStringList list2;
      //用之前清空一下，防止内存泄漏
     list2.clear();
     //从结尾开始逆向遍历
     while(iterator.hasPrevious())
     {
         list2<<(iterator.previous());
     }
      //用之前清空一下，防止内存泄漏
     ui->listWidget->clear();
     ui->listWidget->addItems(list2);
}
void MainWindow::writeSnToServer(const QString& sn,const QString& serverPath)
{
    QFile file(serverPath+"\\Content.txt");
    file.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Append);
    QTextStream in(&file);
    in<< sn <<"\n";
    file.close();
}
void MainWindow::captureScreen(QString sn,QString line,QString machine)
{
     //截图API公共函数抽取
    QString parentPath=ui->lineEdit_ParentPath_0->text();
    QString pathTime = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    QString pathTime2 = QDateTime::currentDateTime().toString("yyyy-MM-dd");
    QString paths= QString("%1 20:00:00").arg(pathTime2);
    QDateTime nowTime = QDateTime::fromString(pathTime,"yyyy-MM-dd HH:mm:ss");
    QDateTime fixedTime = QDateTime::fromString(paths,"yyyy-MM-dd HH:mm:ss");
    uint nowTime_s = nowTime.toTime_t();
    uint fixedTime_s = fixedTime.toTime_t();
    int c = fixedTime_s -nowTime_s;
    this->hide();
    QEventLoop eventloop;
    QTimer::singleShot(270, &eventloop, SLOT(quit()));
    eventloop.exec();
    //  QScreen *screen = QGuiApplication::primaryScreen();
    QDesktopWidget * pDesktoWidget = QApplication::desktop();
    QScreen * pqscreen  = QGuiApplication::primaryScreen() ;
    QPixmap pixmap = pqscreen->grabWindow( pDesktoWidget->winId(), 72,25,1800,940 );
    if(c>0){
        QString datePath = QDateTime::currentDateTime().toString("MMdd");
        QString realPath = parentPath + QString("\\%1\\%2").arg(line).arg(datePath);
        QDir dir(realPath);
        if(!dir.exists())
        {
            dir.mkpath(realPath);
        }
        QString filePathName=NULL;
        filePathName = realPath + "\\" + sn +"__"+machine+"__";
        filePathName +=QDateTime::currentDateTime().toString("zzzz");
        filePathName+="qt";
        filePathName+=".jpg";
        // screen->grabWindow(0).save(filePathName,"jpg");
        pixmap.save(filePathName,"jpg");
        writeSnToServer(sn,realPath);
        this->show();
    }
    if(c<0){
        //创建第二天的文件夹,并存放相应的文件
         QString datePath = QDateTime::currentDateTime().addDays(+1).toString("MMdd");
        QString realPath = parentPath + QString("\\%1\\%2").arg(line).arg(datePath);
        QDir dir(realPath);
        if(!dir.exists())
        {
            dir.mkpath(realPath);
        }
        QString filePathName=NULL;
        filePathName = realPath + "\\" + sn +"__"+machine+"__";
        filePathName +=QDateTime::currentDateTime().toString("zzzz");
        filePathName+="qt";
        filePathName+=".jpg";
        pixmap.save(filePathName,"jpg");
        writeSnToServer(sn,realPath);
        this->show();
    }
}
void MainWindow::captureScreen1(QString sn,QString line)
{
    //截图API公共函数抽取
    QString parentPath=ui->lineEdit_ParentPath_1->text();
    QString pathTime = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    QString pathTime2 = QDateTime::currentDateTime().toString("yyyy-MM-dd");
    QString paths= QString("%1 20:00:00").arg(pathTime2);
    QDateTime nowTime = QDateTime::fromString(pathTime,"yyyy-MM-dd HH:mm:ss");
    QDateTime fixedTime = QDateTime::fromString(paths,"yyyy-MM-dd HH:mm:ss");
    uint nowTime_s = nowTime.toTime_t();
    uint fixedTime_s = fixedTime.toTime_t();
    int c = fixedTime_s -nowTime_s;
    this->hide();
    QEventLoop eventloop;
    QTimer::singleShot(270, &eventloop, SLOT(quit()));
    eventloop.exec();
    //  QScreen *screen = QGuiApplication::primaryScreen();
    QDesktopWidget * pDesktoWidget = QApplication::desktop();
    QScreen * pqscreen  = QGuiApplication::primaryScreen() ;
    QPixmap pixmap = pqscreen->grabWindow( pDesktoWidget->winId(), 72,25,1800,940 );
    if(c>0){
        QString datePath = QDateTime::currentDateTime().toString("MMdd");
        QString realPath = parentPath + QString("\\%1\\%2").arg(line).arg(datePath);
        QDir dir(realPath);
        if(!dir.exists())
        {
            dir.mkpath(realPath);
        }
        QString filePathName=NULL;
        filePathName = realPath + "\\" + sn +"____";
        filePathName +=QDateTime::currentDateTime().toString("zzzz");
        filePathName+="qt";
        filePathName+=".jpg";
        // screen->grabWindow(0).save(filePathName,"jpg");
        pixmap.save(filePathName,"jpg");
        this->show();
    }
    if(c<0){
        //创建第二天的文件夹,并存放相应的文件
        QString datePath = QDateTime::currentDateTime().addDays(+1).toString("MMdd");
        QString realPath = parentPath + QString("\\%1\\%2").arg(line).arg(datePath);
        QDir dir(realPath);
        if(!dir.exists())
        {
            dir.mkpath(realPath);
        }
        QString filePathName=NULL;
        filePathName = realPath + "\\" + sn +"____";
        filePathName +=QDateTime::currentDateTime().toString("zzzz");
        filePathName+="qt";
        filePathName+=".jpg";
        //   screen->grabWindow(0).save(filePathName,"jpg");
        pixmap.save(filePathName,"jpg");
        this->show();
    }
}
void MainWindow::on_pushButton_clicked()
{
    QProcess::execute("mstsc.exe");

    //添加按钮
    //打开txt文本文件
    /*  QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                        "./",
                                                        tr("Text (*.txt)"));
        if (!fileName.isEmpty())
        {
            if (watcher->addPath(fileName))
            {
                //将文件路径添加到列表控件中
                ui->listWidget->addItem(fileName);
            }
        }*/
}

void MainWindow::on_pushButton_2_clicked()
{
    QProcess pro;
    QString path1="\\\\172.26.12.11\\smt_esbu_exe\\MainMenu\\bak\\MainMenu.exe";
    pro.startDetached(path1);

    //删除
  /*  QListWidgetItem* item = ui->listWidget->currentItem();
    if (item)
    {
        if (watcher->removePath(item->text()))
        {
            delete item;
        }
    }*/
}

void MainWindow::on_pushButton_4_clicked()
{
    //模糊按钮代码
    QString searchSn = ui->lineEdit_search->text().toUpper();
    if(searchSn.isEmpty())
    {
        QMessageBox::warning(this,"提示信息","Sn不能为空");
        return;
    }
    QString dateText =  QDateTime::currentDateTime().toString("yyyyMMdd");
    QString path="C:\\SN\\records\\"+dateText+".txt";
    QFile file(path);
    QString text;
    ui->listWidget->clear();
    if (file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        while(!file.atEnd()){
            text= file.readLine().trimmed();
            if(text.contains(searchSn))
            {
                ui->listWidget->addItem(text);
            }
        }
    }
    file.close();
    ui->lineEdit_search->setText("");
    ui->lineEdit_search->setFocus();
}

void MainWindow::on_pushButton_3_clicked()
{
    //截图API公共函数抽取
    QString ma=   ui->lineEdit->text().toUpper();   //V810-xx
    QString line=ui->lineEdit_2->text().toUpper(); //Line
    QString sn=   ui->lineEdit_3->text().toUpper();  // Sn
    if(ma.isEmpty())
    {
        QMessageBox::warning(this,"提示信息","确保框内有值");
        return;
    }
    if(line.isEmpty())
    {
        QMessageBox::warning(this,"提示信息","确保框内有值");
        return;
    }
    if(sn.isEmpty())
    {
        QMessageBox::warning(this,"提示信息","确保框内有值");
        return;
    }
    captureScreen(sn,line,ma);
}

void MainWindow::buziliao(const QString& sndemo)
{
    //补资料的函数的封装
    QDir dirs1("C:\\ITF\\XMLCEXPORT");
    if(!dirs1.exists()){
        dirs1.mkpath("C:\\ITF\\XMLCEXPORT");
    }
    QString filePath=QString("C:\\ITF\\XMLCEXPORT\\%1_#F08-MB-00B0-F3J-DD-01#AXI#system-764#1_012524.xml").arg(sndemo);
    QFile file(filePath);
    file.open(QIODevice::WriteOnly);
    QDomDocument doc;
    QDomProcessingInstruction instruction; //添加处理命令
    instruction=doc.createProcessingInstruction("xml","version=\"1.0\" encoding=\"UTF-8\"");
    doc.appendChild(instruction);
    //添加根节点
    QDomElement root=doc.createElement("ns1:BoardTestXMLExport");
    root.setAttribute("xmlns:ns1","http://tempuri.org/BoardTestXMLExport.xsd");
    root.setAttribute("testTime","2020-04-20T00:02:01.000+08:00");
    root.setAttribute("testerTestStartTime","2020-04-20T00:02:01.000+08:00");
    root.setAttribute("testerTestEndTime","2020-04-20T00:02:14.000+08:00");
    root.setAttribute("numberOfComponentsTested","1");
    root.setAttribute("numberOfJointsTested","1667");
    root.setAttribute("numberOfIndictedComponents","0");
    root.setAttribute("numberOfIndictedPins","0");
    root.setAttribute("numberOfDefects","0");
    root.setAttribute("testStatus","Passed");
    root.setAttribute("repairStatus","Repair None");
    root.setAttribute("repairStationId","3328-VVTS");
    doc.appendChild(root);
    //添加第一个子节点及其子元素
    QDomElement firstNode = doc.createElement("ns1:BoardXML");
    firstNode.setAttribute("serialNumber",sndemo);
    firstNode.setAttribute("imageId","1");
    firstNode.setAttribute("boardType","F20-MB-00Y0-E3N-DD-02");
    firstNode.setAttribute("boardRevision","1587312134000");
    firstNode.setAttribute("assemblyRevision","F20-MB-00Y0-E3N-DD-02");
    root.appendChild(firstNode);
    QDomElement secNode=doc.createElement("ns1:StationXML");
    secNode.setAttribute("testerName","V810-8086S2");
    secNode.setAttribute("stage","v810");
    root.appendChild(secNode);
    QDomElement threeNode=doc.createElement("ns1:RepairEventXML");
    threeNode.setAttribute("repairStartTime","2020-04-20T00:02:16.000+08:00");
    threeNode.setAttribute("repairEndTime","2020-04-20T00:03:59.000+08:00");
    threeNode.setAttribute("repairOperator","c_admin");
    threeNode.setAttribute("numberOfActiveDefects","0");
    threeNode.setAttribute("numberOfActiveComponents","0");
    threeNode.setAttribute("numberOfActivePins","0");
    threeNode.setAttribute("numberOfFalseCalledDefects","0");
    threeNode.setAttribute("numberOfFalseCalledComponents","0");
    threeNode.setAttribute("numberOfFalseCalledPins","0");
    threeNode.setAttribute("numberOfRepairedDefects","0");
    threeNode.setAttribute("numberOfRepairedComponents","0");
    threeNode.setAttribute("numberOfRepairedPins","0");
    threeNode.setAttribute("numberOfRepairLaterDefects","0");
    threeNode.setAttribute("numberOfRepairLaterComponents","0");
    threeNode.setAttribute("numberOfRepairLaterPins","0");
    threeNode.setAttribute("numberOfVariationOkDefects","0");
    threeNode.setAttribute("numberOfVariationOkComponents","0");
    threeNode.setAttribute("numberOfVariationOkPins","0");
    root.appendChild(threeNode);
    QTextStream out_stream(&file);
    doc.save(out_stream,4); //缩进4格
    file.close();
}
void MainWindow::on_pushButton_6_clicked()
{
    //置顶
 //  this->setWindowFlags(Qt::WindowStaysOnTopHint);

    Qt::WindowFlags m_flags = windowFlags();

      this->setWindowFlags(m_flags | Qt::WindowStaysOnTopHint);
    show();
}

void MainWindow::on_pushButton_7_clicked()
{
    //取消置顶
   // this->setWindowFlags(this->windowFlags());
 // QString  m_flags = NULL;
       // setWindowFlags(NULL);
     //   show();
 //   ::SetWindowPos(HWND(this->winId()), HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);

 //  setWindowFlags(Qt::Widget);

    this->close();

}

void MainWindow::on_pushButton_5_clicked()
{
    //bu
    //123123123_#F08-MB-00B0-F3J-DD-01#AXI#system-764#1_012524
    QString sn = ui->lineEdit_6->text().toUpper();
    if(sn.isEmpty())
    {
        QMessageBox::warning(this,"提示信息","请键入Sn");
        return;
    }
    buziliao(sn);
    ui->lineEdit_6->setText("");
    ui->lineEdit_6->setFocus();
}

void MainWindow::on_pushButton_BTN_L22_clicked()
{
    QString line = ui->lineEdit_LineL22->text();
    QString sn = ui->lineEdit_SnL22->text();
    if(line.isEmpty())
    {
        QMessageBox::warning(this,"提示","确保框内有值");
        return;
    }
    if(sn.isEmpty())
    {
        QMessageBox::warning(this,"提示","确保框内有值");
        return;
    }
    captureScreen1(sn,line);
    ui->lineEdit_SnL22->setText("");
    ui->lineEdit_SnL22->setFocus();
}

void MainWindow::on_pushButton_BTN_L12_clicked()
{
    QString line = ui->lineEdit_LineL12->text();
    QString sn = ui->lineEdit_SnL12->text();
    if(line.isEmpty())
    {
        QMessageBox::warning(this,"提示","确保框内有值");
        return;
    }
    if(sn.isEmpty())
    {
        QMessageBox::warning(this,"提示","确保框内有值");
        return;
    }
    captureScreen1(sn,line);
    ui->lineEdit_SnL12->setText("");
    ui->lineEdit_SnL12->setFocus();
}

void MainWindow::on_pushButton_BTN_K12_clicked()
{
    QString line = ui->lineEdit_LineK12->text();
    QString sn = ui->lineEdit_SnK12->text();
    if(line.isEmpty())
    {
        QMessageBox::warning(this,"提示","确保框内有值");
        return;
    }
    if(sn.isEmpty())
    {
        QMessageBox::warning(this,"提示","确保框内有值");
        return;
    }
    captureScreen1(sn,line);
    ui->lineEdit_SnK12->setText("");
    ui->lineEdit_SnK12->setFocus();
}

void MainWindow::on_pushButton_BTN_K22_clicked()
{
    QString line = ui->lineEdit_LineK22->text();
    QString sn = ui->lineEdit_SnK22->text();
    if(line.isEmpty())
    {
        QMessageBox::warning(this,"提示","确保框内有值");
        return;
    }
    if(sn.isEmpty())
    {
        QMessageBox::warning(this,"提示","确保框内有值");
        return;
    }
    captureScreen1(sn,line);
    ui->lineEdit_SnK22->setText("");
    ui->lineEdit_SnK22->setFocus();
}
void MainWindow::on_radioButton_clicked()
{
    // tab1 75
    ui->lineEdit_ParentPath_0->setText("\\\\172.26.120.75\\aoiaxi\\AXI\\5DX\\5DX不良");
    ui->radioButton->setChecked(true);
    ui->radioButton_2->setChecked(false);
}

void MainWindow::on_radioButton_2_clicked()
{
    //tab1 16
    ui->lineEdit_ParentPath_0->setText("\\\\172.26.12.16\\aoi\\5DX\\5DX不良");
    ui->radioButton->setChecked(false);
    ui->radioButton_2->setChecked(true);
}

void MainWindow::on_radioButton_3_clicked()
{
    //tab2 75
    ui->lineEdit_ParentPath_1->setText("\\\\172.26.120.75\\aoiaxi\\AXI\\5DX\\5DX不良");
    ui->radioButton_3->setChecked(true);
    ui->radioButton_4->setChecked(false);
}

void MainWindow::on_radioButton_4_clicked()
{
    //tab2 16
    ui->lineEdit_ParentPath_1->setText("\\\\172.26.12.16\\aoi\\5DX\\5DX不良");
    ui->radioButton_3->setChecked(false);
    ui->radioButton_4->setChecked(true);
}

void MainWindow::on_pushButton_8_clicked()
{
    ui->listWidget->clear();
    ui->listWidget_2->clear();
}

void MainWindow::on_listWidget_customContextMenuRequested(const QPoint &pos)
{
    QListWidgetItem *item = ui->listWidget->itemAt(pos);
        if(item==NULL)
            return;
        QMenu *menu = new QMenu(this);
        QAction *act1 = new QAction("截图", this);
        QAction *act2 = new QAction("复制Sn", this);
        menu->addAction(act1);
        menu->addAction(act2);
//        qDebug()<<item->text();
 //       QString items= item->text();
        connect(act1, SIGNAL(triggered()), this, SLOT(my_slot_snipping()));
        connect(act2, SIGNAL(triggered()), this, SLOT(my_slot_snipping1()));
        menu->exec(QCursor::pos()); //在鼠标位置弹出菜单
        delete menu;
        delete act1;
}

void MainWindow::my_slot_snipping1()
{
    QString item;
         QList<QListWidgetItem *> list=ui->listWidget->selectedItems ();
         foreach(QListWidgetItem * a,list)
         {
              item=a->text();
              // QMessageBox::warning(this,"提示信息",a->text());
         }

QString sn= item.split('_')[0].toUpper();  // Sn
QClipboard *clipboard = QApplication::clipboard();
clipboard->setText(sn);
}
void MainWindow::my_slot_snipping()
{
    QString item;
         QList<QListWidgetItem *> list=ui->listWidget->selectedItems ();
         foreach(QListWidgetItem * a,list)
         {
              item=a->text();
              // QMessageBox::warning(this,"提示信息",a->text());
         }
     QString ma=  item.split('_')[2].toUpper();   //V810-xx
    QString line=item.split('_')[1].toUpper(); //Line
    QString sn= item.split('_')[0].toUpper();  // Sn
    if(ma.isEmpty())
    {
        QMessageBox::warning(this,"提示信息","确保框内有值");
        return;
    }
    if(line.isEmpty())
    {
        QMessageBox::warning(this,"提示信息","确保框内有值");
        return;
    }
    if(sn.isEmpty())
    {
        QMessageBox::warning(this,"提示信息","确保框内有值");
        return;
    }
    captureScreen(sn,line,ma);
}
void MainWindow::on_tabWidget_tabBarClicked(int index)
{
    if(index==0)
    {
        ui->tabWidget->setFixedHeight(416);
        ui->tabWidget->setFixedWidth(600);
        this->resize(316,328);
    }
    if(index==1)
    {
       ui->tabWidget->setFixedHeight(327);
       ui->tabWidget->setFixedWidth(310);
       this->resize(321,327);
    }
    if(index==2)
    {
        ui->tabWidget->setFixedHeight(340);
        ui->tabWidget->setFixedWidth(270);
        this->resize(320,300);
    }
}

void MainWindow::on_pushButton_11_clicked()
{
    //sop
    QDesktopServices::openUrl(QUrl("http://172.26.8.79/e_sop/Users/SignIn.aspx"));

}

void MainWindow::on_pushButton_9_clicked()
{
    QDesktopServices::openUrl(QUrl("file:\\\\172.26.120.75\\aoiaxi\\AXI\\5DX\\5DX不良\\", QUrl::TolerantMode));

}

void MainWindow::on_pushButton_10_clicked()
{
    QDesktopServices::openUrl(QUrl("file:\\\\172.26.12.16\\aoi\\5DX\\5DX不良\\", QUrl::TolerantMode));

}

void MainWindow::on_pushButton_12_clicked()
{
    //itf
    QString realPath = QString("C:\\ITF\\XMLCEXPORT");
    QDir dir(realPath);
    if(!dir.exists())
    {
        QMessageBox::warning(this,"提示信息","请检查是否存在该路径");
        return;
    }
    QDesktopServices::openUrl(QUrl::fromLocalFile("C:\\ITF\\XMLCEXPORT"));
}

void MainWindow::on_pushButton_13_clicked()
{
    //Cbackup
    QString pathTime2 = QDateTime::currentDateTime().toString("yyyyMMdd");
    QString realPath = QString("C:\\AXI\\CBackup\\%1").arg(pathTime2);
    QDir dir(realPath);
    if(!dir.exists())
    {
        QMessageBox::warning(this,"提示信息","请检查是否存在该路径");
        return;
    }
    QDesktopServices::openUrl(QUrl::fromLocalFile("C:\\AXI\\CBackup\\"+pathTime2));
}
