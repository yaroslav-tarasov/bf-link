#ifndef NETLINK_SOCKET_H
#define NETLINK_SOCKET_H

#include <QObject>
#include <memory>

class NetlinkSocketPrivate;

class NetlinkSocket : public QObject
{
    Q_OBJECT
public:
    explicit NetlinkSocket(QObject *parent = 0);
    void     SendMsg(void* msg,size_t size);
    void     Create();
protected:

signals:
    void error(QString err);
    void readyRead();

protected:
   std::shared_ptr<NetlinkSocketPrivate> d;
   int mProto;
   int mBuffSize;
};

#endif // NETLINK_SOCKET_H
