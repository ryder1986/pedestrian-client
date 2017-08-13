#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QObject>
#include <QtNetwork>
#include <QMessageBox>
#include <QTcpSocket>
#include <QDataStream>
#include <QFile>
class client : public QObject
{
    Q_OBJECT
public:
    client(){
        tcp_socket=new QTcpSocket();

        connect(tcp_socket, &QIODevice::readyRead, this, &client::read_msg);
        //  f->open(tcp_socket,QFile::ReadOnly);

        in.setDevice(tcp_socket);
        in.setVersion(QDataStream::Qt_1_0);
        udp_skt=new QUdpSocket(this);
        udp_skt->bind(45454,QUdpSocket::ShareAddress);
    }
    void read_msg()
    {
        //        in.setDevice(tcp_socket);
        //        in.setVersion(QDataStream::Qt_4_0);
        //        in.startTransaction();

        static  char buf[100];

        //    int len=3;
        //  in.readBytes(buf,len);
        int ret=  in.readRawData((char *)buf,3);
        //   int ret=  in.readBytes((char &)buf,len);

        // QString nextFortune;
        //in >> nextFortune;
        qDebug()<<QString::fromRawData((QChar *)buf,3);
        //        if (!in.commitTransaction())
        //            return;

    }

    void search()
    {
        while(udp_skt->hasPendingDatagrams()){

            datagram.resize((udp_skt->pendingDatagramSize()));
            udp_skt->readDatagram(datagram.data(),datagram.size());
            qDebug()<<"get"<<datagram.data();
        }
    }
signals:

public slots:
    void request_msg()
    {
        tcp_socket->connectToHost("192.168.1.216",12345);
    }



    void  displayError(QAbstractSocket::SocketError socketError)
    {
        switch (socketError) {
        case QAbstractSocket::RemoteHostClosedError:
            break;
        case QAbstractSocket::HostNotFoundError:
            qDebug()<<"1";
            break;
        case QAbstractSocket::ConnectionRefusedError:
            qDebug()<<"1";
            break;
        default:
            qDebug()<<"1";
        }

        //  getFortuneButton->setEnabled(true);
    }

private:
    QTcpSocket *tcp_socket;
    QDataStream in;
    QFile *f;



    QUdpSocket *udp_skt;
    QByteArray datagram;
};

#endif // CLIENT_H
