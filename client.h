#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QObject>
#include <QtNetwork>
#include <QMessageBox>
#include <QTcpSocket>
#include <QDataStream>
#include <QFile>
#include <QThread>
class Client : public QObject
{
    Q_OBJECT
public:
    Client(){
        tcp_socket=new QTcpSocket();

        connect(tcp_socket, &QIODevice::readyRead, this, &Client::read_msg);
        //  f->open(tcp_socket,QFile::ReadOnly);

        in.setDevice(tcp_socket);
        in.setVersion(QDataStream::Qt_1_0);
        udp_skt=new QUdpSocket(this);
        udp_skt->bind(12347,QUdpSocket::ShareAddress);
      //  broadcast_to_client();
      //  search();
    }
    void broadcast_to_client()
    {

        QByteArray b;
        b.append("1234");
        udp_skt->writeDatagram(b.data(), b.size(),
                               QHostAddress::Broadcast, 12346);
     //   prt(info,"printing..");
        qDebug()<<QString(b)<<"send";
    }

    void pack_tcp_data(char *c,int length){

        quint16  *pos_version=( quint16  *)c+2;
        quint16 *pos_length=( quint16  *)c;
        *pos_version=1;
        *pos_length=length;
    }
    char buf[10000];
    void get_client_setting(){
        qDebug()<<"try to get server setting";
        char *data=buf;
        quint16 *pos_op=(quint16 *)(data+4);
        *pos_op=0;

        pack_tcp_data(buf,0);
        int ret=tcp_socket->write(buf,6);
        qDebug()<<"ret "<<ret;
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
        //  while(udp_skt->hasPendingDatagrams())
        if(udp_skt->hasPendingDatagrams())

        {

            datagram.resize((udp_skt->pendingDatagramSize()));
            udp_skt->readDatagram(datagram.data(),datagram.size());
            qDebug()<<"get"<<datagram.data();
        }
    }
    void search_device()
    {

    }

    QByteArray  call_server(char *buf,int len)
    {
        QByteArray ret;
        ret.resize(0);
        char  bf[1000];
        tcp_socket->write(buf,len);
     //   QThread::msleep(3000);
      if(tcp_socket->waitForReadyRead())
          //      tcp_socket->read(bf,300);
       ret=tcp_socket->readAll();
        return ret;
    }


signals:

public slots:
    void connect_to_server()
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
