#include "udpcom.h"

UDPCOM::UDPCOM(MainWindow *mainw, QString MyAddress1, QString DestineAddress1, int MyPort1, int DestinePort1)
{
    MyAddress = MyAddress1;
    DestineAddress = DestineAddress1;
    DestinePort = DestinePort1;
    MyPort = MyPort1;

    myMain = mainw;
    udpSocketOut = new QUdpSocket(mainw);
    udpSocketOut->bind(QHostAddress(DestineAddress), DestinePort);

    udpSocketIn = new QUdpSocket(mainw);
    udpSocketIn->bind(QHostAddress(MyAddress), MyPort);
    mainw->connect(udpSocketIn, SIGNAL(readyRead()),mainw, SLOT(readPendingDatagrams()));
}

UDPCOM::~UDPCOM()
{

}

QString UDPCOM::UDPread()
{
    QString lido;
    while (udpSocketIn->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udpSocketIn->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        udpSocketIn->readDatagram(datagram.data(), datagram.size(),
                                &sender, &senderPort);
        lido += datagram;
    }
    return lido;
}

void UDPCOM::UDPwrite(QString txt)
{
    QByteArray datagram;
    datagram.append(txt);
    udpSocketOut->writeDatagram(datagram,QHostAddress(DestineAddress), DestinePort);
}

