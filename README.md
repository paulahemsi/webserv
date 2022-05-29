# webserv

* [introduction](#introduction)
* [socket](#socket)
* [specific_functions_overview](#specific_functions_overview)
* [study resources](#study_resources)

## introduction

The Hypertext Transfer Protocol (HTTP) is an application protocol for distributed, collaborative, hypermedia information systems.

HTTP is the foundation of data communication for the World Wide Web, where hypertext documents include hyperlinks to other resources that the user can easily access. For example, by a mouse click or by tapping the screen in a web browser.

HTTP was developed to facilitate hypertext and the World Wide Web.

The primary function of a web server is to store, process, and deliver web pages to clients. The communication between client and server takes place using the Hypertext
Transfer Protocol (HTTP).

Pages delivered are most frequently HTML documents, which may include images, style sheets, and scripts in addition to the text content.

Multiple web servers may be used for a high-traffic website.

A user agent, commonly a web browser or web crawler, initiates communication by requesting a specific resource using HTTP and the server responds with the content of
that resource or an error message if unable to do so. The resource is typically a real file on the server’s secondary storage, but this is not necessarily the case and depends on how the webserver is implemented.

While the primary function is to serve content, full implementation of HTTP also includes ways of receiving content from clients. This feature is used for submitting web
forms, including the uploading of files.

## socket

A socket is the mechanism that most popular operating systems provide to give programs access to the network. It allows messages to be sent and received between applications (unrelated processes) on different networked machines.

The sockets mechanism has been created to be independent of any specific type of network. IP, however, is by far the most dominant network and the most popular use of sockets.

There are a few steps involved in using sockets:

* Create the socket
* Identify the socket
* On the server, wait for an incoming connection
* Send and receive messages
* Close the socket

From [HTTP Server: Everything you need to know to Build a simple HTTP server from scratch](https://medium.com/from-the-scratch/http-server-what-do-you-need-to-know-to-build-a-simple-http-server-from-scratch-d1ef8945e4fa)

## specific_functions_overview

<details>
  <summary>Click to expand</summary>
  
  
  
| function | description | return value |
|----------|-------------|--------------|
| uint16_t **htons** _(uint16_t hostshort);_| converts the unsigned **short** integer **hostshort** **from host** byte order **to network** byte order. |uint16_t|
|uint32_t **htonl** _(uint32_t hostlong);_| converts the unsigned integer hostlong **from host** byte order **to network** byte order.| uint32_t|
|uint16_t **ntohs** _(uint16_t netshort);_|converts the unsigned **short** integer netshort **from network** byte order **to host** byte order.|uint16_t|
|uint32_t **ntohl** _(uint32_t netlong);_|converts the unsigned integer netlong **from network** byte order **to host** byte order.|uint32_t|
|int **select** _(int nfds, fd_set * readfds, fd_set * writefds, fd_set * exceptfds, struct timeval * timeout);_| allow a program to monitor multiple file descriptors, waiting until one or more of the file descriptors become "ready" for some class of I/O  operation | On  success return the number of file descriptors contained in the three returned descriptor sets.  On error, -1 is returned, and errno is set to indicate the error; the  file  descriptor sets are unmodified, and timeout becomes undefined.|
|int **poll** _(struct pollfd * fds, nfds_t nfds, int timeout);_|performs a similar task to select: it waits for one of a set of file descriptors to become ready to perform I/O.|On success, a positive number is returned; this is the number of structures which have nonzero revents fields (in other words, those descriptors with events or errors reported).  A value of 0 indicates that the call timed out and no file descriptors were ready. On error, -1 is returned, and errno is set appropriately.|
|int **epoll_create** _(int size);_ |creates a new epoll instance.|returns a file descriptor referring to the new epoll instance. This file descriptor is used for all the subsequent calls to the epoll interface. When no longer required, the file descriptor returned by epoll_create() should be closed by  using close. When all file descriptors referring to an epoll instance have been closed, the kernel destroys the instance and releases the associated resources for reuse. On error, -1 is returned, and errno is set to indicate the error.|
|int **epoll_ctl** _(int epfd, int op, int fd, struct epoll_event * event);_|is used to add, modify, or remove entries in the interest list of the epoll instance referred to by the file descriptor epfd. It requests that the operation op be performed for the target file descriptor, fd.|When successful, epoll_ctl() returns zero. When an error occurs, epoll_ctl() returns -1 and errno is set appropriately.|
|int **epoll_wait** _(int epfd, struct epoll_event * events, int maxevents, int timeout);_|waits for events on the epoll(7) instance referred to by the file          descriptor epfd.  The memory area pointed to by events will contain the events that will be available  for the caller. Up to maxevents are returned by epoll_wait().  The maxevents argument must be greater than zero. | When  successful,  epoll_wait() returns the number of file descriptors ready for the requested I/O, or zero if no file descriptor became ready during  the  requested  timeout  milliseconds. When an error occurs, epoll_wait() returns -1 and errno is set appropriately. |
|**kqueue**| | |
|**kevent**| | |
| int **socket** _(int domain, int type, int protocol);_|socket()  creates  an  endpoint  for communication and returns a file descriptor that refers to that endpoint.| On success, a file descriptor for the new socket is returned.  On error, -1 is returned, and errno is set  appropriately. |
|int **accept** _(int sockfd, struct sockaddr *addr, socklen_t *addrlen);_|The  accept()  system  call is used with connection-based socket types (SOCK_STREAM, SOCK_SEQPACKET). It extracts the first connection request on the queue of pending connections for the listening socket, sockfd, creates a new connected socket, and returns a new file descriptor referring to that socket. The newly created socket is not in the listening state. The original socket sockfd is unaffected by this call. |On success, these system calls return a nonnegative integer that is a file descriptor for the accepted  socket. On error, -1 is returned, errno is set appropriately, and addrlen is left unchanged. |
|int **listen** _(int sockfd, int backlog);_ | listen() marks the socket referred to by sockfd as a passive socket, that is, as a socket that will be used to accept incoming connection requests using accept |On success, zero is returned.  On error, -1 is returned, and errno is set appropriately. |
|ssize_t **send** _(int sockfd, const void *buf, size_t len, int flags);_ |used to transmit a message to another socket.|On success, these calls return the number of bytes sent. On error, -1 is returned, and  errno is set appropriately.|
|ssize_t **recv** _(int sockfd, void *buf, size_t len, int flags);_|used to receive messages from a socket.|These calls return the number of bytes received, or -1 if an error occurred. In the event of an error, errno is set to indicate the error.|
|int **bind** _(int sockfd, const struct sockaddr * addr, socklen_t addrlen);_| When a socket is created with socket(2), it exists in a name space (address family) but has no a|ddress assigned to it. bind() assigns the address specified by addr to the socket referred to by the file descriptor sockfd. addrlen specifies the size, in bytes, of the address structure pointed to by addr. Traditionally, this operation is called “assigning a name to a socket”.|On success, zero is returned.  On error, -1 is returned, and errno is set appropriately.|
|int **connect** _(int sockfd, const struct sockaddr * addr, socklen_t addrlen);_| connects the socket referred to by the file descriptor sockfd to the address specified by addr. The addrlen argument specifies the size of addr. The format of the address in addr is determined by the address space of the socket sockfd; |If the connection or binding succeeds, zero is returned. On error, -1 is returned, and  errno is set appropriately.|
|in_addr_t **inet_addr** _(const char *cp)_; |converts the Internet host address cp from IPv4 numbers-and-dots notation into binary data in network byte order.|If the input is invalid, INADDR_NONE (usually -1) is returned. Use of this function is problematic because -1 is a valid address (255.255.255.255). Avoid its use in favor of inet_aton, inet_pton, or getaddrinfo, which provide a cleaner way to indicate error return. |
|int **setsockopt** _(int sockfd, int level, int optname, const void *optval, socklen_t optlen);_|manipulate options for the socket referred to by the file descriptor sockfd. Options may exist at multiple protocol levels; they are always present at the uppermost socket level. | On success, zero is returned for the standard options.  On error, -1 is returned, and errno is set appropriately. Netfilter allows the programmer to define custom socket options with associated handlers; for such options,     the return value on success is the value returned by the handler. |
|int **getsockname** _(int sockfd, struct sockaddr *addr, socklen_t *addrlen);_|returns the current address to which the socket sockfd is bound, in the buffer pointed to by addr. The addrlen argument should be initialized to indicate the amount of space (in  bytes) pointed to by addr. On return it contains the actual size of the socket address. The  returned  address  is  truncated if the buffer provided is too small; in this case, addrlen will return a value greater than was supplied to the call. | On success, zero is returned.  On error, -1 is returned, and errno is set appropriately. |
|int **fcntl** _(int fd, int cmd, ... /* arg */ );_| performs one of the operations described below on the open file descriptor fd. The operation is determined by cmd. |For a successful call, the return value depends on the operation (see the **hugr** man page).  On error, -1 is returned, and errno is set appropriately. |


 </details>
 
 
## study_resources

* [Overview Of World Wide Web by Arif Butt](https://www.youtube.com/watch?v=Ls2G6HjvkYc&list=PL7B2bn3G_wfD6_mhy-eLdn_mFgQ_mOyLl&index=11)
* [HTTP Server: Everything you need to know to Build a simple HTTP server from scratch](https://medium.com/from-the-scratch/http-server-what-do-you-need-to-know-to-build-a-simple-http-server-from-scratch-d1ef8945e4fa)
