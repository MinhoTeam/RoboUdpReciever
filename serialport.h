#ifndef SERIALPORT_H
#define SERIALPORT_H

#include "mainwindow.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QMessageBox>

class SerialPort
{

private slots:
    bool ConnectSerial();
    MainWindow *myMain;
public:
    QSerialPort serial;
    QString readAll();
    void write(QString txt);
    SerialPort(MainWindow *mainw,QString name, int baudRate);
    ~SerialPort();
private:
    QByteArray frameToSend;
};

#endif // SERIALPORT_H
