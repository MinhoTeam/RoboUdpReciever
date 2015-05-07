#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "serialport.h"
#include "udpcom.h"

SerialPort *mySerial;
UDPCOM *udp;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QFile file("configs.txt");

    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
    }
    QTextStream in(&file);
    QStringList lines;
    while(!in.atEnd()) {
        QString lido = in.readLine();
        lido = lido.remove(lido.indexOf("#"),lido.length());
        qDebug() << lido;
        lines.append(lido);
    }
    file.close();

    if(lines.length()==6)
    {
        mySerial = new SerialPort(this,lines.at(0),lines.at(1).toInt());
        //MyAddress,DestinationAddress,MyPort,DestinationPort
        udp = new UDPCOM(this,lines.at(2),lines.at(3),lines.at(4).toInt(),lines.at(5).toInt());
    }
    else QMessageBox::information(this,"Error: ","Configs txt not OK!: "+QString::number(lines.length()));

    UDPSenderTimer = new QTimer();
    connect(UDPSenderTimer,SIGNAL(timeout()),this,SLOT(sendRoboData()));
    UDPSenderTimer->start(100);//10fps
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::readResponse()
{
    lidoSerial += mySerial->readAll();
    if(lidoSerial.contains(":") && lidoSerial.contains("\n")){
        lidoSerial.replace("\n","");
        lidoSerial.replace(":","");
        LowLevelData = lidoSerial;
        lidoSerial = "";
    }
}

void MainWindow::readPendingDatagrams()
{
   lidoUDP += udp->UDPread();
   if(lidoUDP.contains(":") && lidoUDP.contains("\n")){
       lidoUDP.replace(":","");
       mySerial->write(lidoUDP);
       qDebug() << lidoUDP;
       lidoUDP = "";
   }
}

void MainWindow::sendRoboData()
{
    udp->UDPwrite(LowLevelData);
}

