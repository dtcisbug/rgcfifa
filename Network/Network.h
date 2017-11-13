#ifndef _NETWORK_H_
#define _NETWORK_H_

#include "Common/Config.h"

#ifdef _WIN32

#include <winsock2.h>
#include <errno.h>
#ifndef EWOULDBLOCK
#define EWOULDBLOCK WSAEWOULDBLOCK
#define EINPROGRESS WSAEINPROGRESS
#define ECONNRESET WSAECONNRESET
#define ENETRESET WSAENETRESET
#endif
#ifndef ENOMEM
#define EINTR WSAEINTR
#define EFAULT WSAEFAULT
#define ENOMEM WSA_NOT_ENOUGH_MEMORY
#define EAGAIN WSATRY_AGAIN
#endif

#ifndef HAVE_SOCKLEN_T
#define HAVE_SOCKLEN_T
typedef int socklen_t;
#endif

#ifndef _SSIZE_T_
#define _SSIZE_T_
typedef long _ssize_t;

typedef _ssize_t ssize_t;
#endif

#define SOCKET_ERRNO() WSAGetLastError()

#else

#define SOCKET_ERRNO() (errno)

#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <netdb.h>
#ifndef SOCKET_ERROR
#define SOCKET_ERROR (-1)
#endif

#endif

#define make_linger(s) \
{ \
struct linger so_linger; \
	so_linger.l_onoff = 1; \
	so_linger.l_linger = 0; \
	setsockopt(s, SOL_SOCKET, SO_LINGER, (const char *)&so_linger, sizeof(so_linger)); \
}

#define make_no_linger(s) \
{ \
struct linger so_linger; \
	so_linger.l_onoff = 0; \
	so_linger.l_linger = 0; \
	setsockopt(s, SOL_SOCKET, SO_LINGER, (const char *)&so_linger, sizeof(so_linger)); \
}

namespace Network
{
#ifdef _WIN32
	inline int close(int s) { return closesocket(s); }
	inline int read(int fd, char * buf, int len) {return recv(fd, buf, len, 0);}
	inline int write(int fd, char * buf, int len) {return send(fd, buf, len, 0);}
#endif
	void Initialize();
	void Uninitialize();
	UInt32 ResolveAddress( const char * domain );
}

#endif // _NETWORK_H_
