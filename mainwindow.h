#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void readResponse();
    void readPendingDatagrams();
    void sendRoboData();
private:
    Ui::MainWindow *ui;
    QString LowLevelData,lidoSerial,lidoUDP;
    QTimer *UDPSenderTimer;

};

#endif // MAINWINDOW_H
