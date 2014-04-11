#include "netlink_socket.h"
#include <QTcpSocket>
#include <QDebug>
#include <linux/if_ether.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netlink/netlink.h>
#include <netlink/handlers.h>
#include "trx_data.h"
/////
//
//    По мотивам http://linux-development-for-fresher.blogspot.ru/2012/05/understanding-netlink-socket.html
//

class NetlinkSocketPrivate 
{
public:  
  explicit NetlinkSocketPrivate(NetlinkSocket * pp){};
  ~NetlinkSocketPrivate(){};
  
   QTcpSocket usock;
  int    sock_fd;
  struct sockaddr_nl src_addr;
  struct sockaddr_nl dest_addr;
};

NetlinkSocket::NetlinkSocket(QObject *parent) :
    QObject(parent)
{
    d.reset(new NetlinkSocketPrivate(this));

}

void NetlinkSocket::Create()
{
  d->sock_fd = socket(PF_NETLINK, SOCK_RAW,NETLINK_USERSOCK);
  
  memset(&d->src_addr, 0, sizeof(d->src_addr));
  d->src_addr.nl_family = AF_NETLINK;
  d->src_addr.nl_pid = getpid(); /* self pid */
  d->src_addr.nl_groups = 0; /* not in mcast groups */
  bind(d->sock_fd, (struct sockaddr*)&d->src_addr,
                        sizeof(d->src_addr));

  memset(&d->dest_addr, 0, sizeof(d->dest_addr));
  d->dest_addr.nl_family = AF_NETLINK;
  d->dest_addr.nl_pid = 0;   /* For Linux Kernel */
  d->dest_addr.nl_groups = 0; /* unicast */

  // http://qt-project.org/forums/viewthread/7714

  bool ret = d->usock.setSocketDescriptor(d->sock_fd);
  qDebug() << "setSocketDescriptor = " << ret;

  connect(&d->usock, SIGNAL(readyRead()),
             this, SIGNAL(readyRead()));
}

void NetlinkSocket::SendMsg(int type,void* msg,size_t size)
{
        struct iovec iov;
        struct msghdr msghdr;
        struct nlmsghdr * nlh=(struct nlmsghdr *)malloc(NLMSG_SPACE(size));
        /* Fill the netlink message header */
        nlh->nlmsg_len = NLMSG_SPACE(NLMSG_SPACE(size));
        nlh->nlmsg_pid = getpid(); /* self pid */
        nlh->nlmsg_flags = 0;
        nlh->nlmsg_type = type;
        /* Fill in the netlink message payload */
        memcpy(NLMSG_DATA(nlh), msg, size);

        iov.iov_base = (void *)nlh;
        iov.iov_len = nlh->nlmsg_len;
        msghdr.msg_name = (void *)&d->dest_addr;
        msghdr.msg_namelen = sizeof(d->dest_addr);
        msghdr.msg_iov = &iov;
        msghdr.msg_iovlen = 1;

        sendmsg(d->sock_fd, &msghdr, 0);
      
}
