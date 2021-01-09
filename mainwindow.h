#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileSystemWatcher>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void  handleTimeout();  //超时处理函数
    virtual void timerEvent( QTimerEvent *event);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    //点击添加按钮，添加要监视的文件

    //点击删除按钮，删除不需要监视的文件

    //当监视的文本文件发生变化时，
    //读取文本内容，并更新到右侧文本编辑器中
    void onFileChanged(const QString& path);




    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();





    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_BTN_L22_clicked();

    void on_pushButton_BTN_L12_clicked();

    void on_pushButton_BTN_K12_clicked();

    void on_pushButton_BTN_K22_clicked();

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_3_clicked();

    void on_radioButton_4_clicked();

    void on_pushButton_8_clicked();

    void on_listWidget_customContextMenuRequested(const QPoint &pos);
    void my_slot_snipping();
     void my_slot_snipping1();
     void on_tabWidget_tabBarClicked(int index);

     void on_pushButton_11_clicked();

     void on_pushButton_9_clicked();

     void on_pushButton_10_clicked();

     void on_pushButton_12_clicked();

     void on_pushButton_13_clicked();

private:
    Ui::MainWindow *ui;
    QFileSystemWatcher* watcher;//监视器指针
    void captureScreen(QString sn,QString line,QString machine);
    void captureScreen1(QString sn,QString line);
    void buziliao(const QString& sndemo);
    void writeSnToServer(const QString& sn,const QString& serverPath);
    int m_nTimerID;
    QString fileWatcherPath;
};

#endif // MAINWINDOW_H
