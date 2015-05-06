#include "serialport.h"

bool SerialPort::ConnectSerial()
{
    if (serial.open(QIODevice::ReadWrite))
    {
        myMain->connect(&serial, SIGNAL(readyRead()),myMain, SLOT(readResponse()));
        QMessageBox msgBox;
        msgBox.setText("Open!");
        msgBox.exec();
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Erro: "+serial.errorString());
        msgBox.exec();

    }
    return true;
}

QString SerialPort::readAll()
{
    return serial.readAll();
}

void SerialPort::write(QString txt)
{
    frameToSend.append(txt);
    serial.write(frameToSend);
    frameToSend.clear();
}

SerialPort::SerialPort(MainWindow *mainw, QString name, int baudRate)
{
    myMain = mainw;
    serial.setPortName(name);
    serial.setBaudRate(baudRate);
    ConnectSerial();
}

SerialPort::~SerialPort()
{

}

