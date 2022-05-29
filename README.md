# webserv

* [introduction](#introduction)
* [socket](#socket)
* [specific_functions_overview](#specific_functions_overview)
* [study resources](#study_resources)

# introduction

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
| uint16_t htons(uint16_t hostshort);| converts the unsigned **short** integer **hostshort** **from host** byte order **to network** byte order. |uint16_t|
|uint32_t htonl(uint32_t hostlong);| converts the unsigned integer hostlong **from host** byte order **to network** byte order.| uint32_t|
|uint16_t ntohs(uint16_t netshort);|converts the unsigned **short** integer netshort **from network** byte order **to host** byte order.|uint16_t|
|uint32_t ntohl(uint32_t netlong);|converts the unsigned integer netlong **from network** byte order **to host** byte order.|uint32_t|
|int select(int nfds, fd_set * readfds, fd_set * writefds, fd_set * exceptfds, struct timeval * timeout);| allow a program to monitor multiple file descriptors, waiting until one or more of the file descriptors become "ready" for some class of I/O  operation | On  success return the number of file descriptors contained in the three returned descriptor sets.  On error, -1 is returned, and errno is set to indicate the error; the  file  descriptor sets are unmodified, and timeout becomes undefined.|
|int poll(struct pollfd * fds, nfds_t nfds, int timeout);|performs a similar task to select(2): it waits for one of a set of file descriptors to become ready to perform I/O.|On success, a positive number is returned; this is the number of structures which have nonzero revents fields (in other words, those descriptors with events or errors reported).  A value of 0 indicates that the call timed out and no file descriptors were ready. On error, -1 is returned, and errno is set appropriately.|
|int epoll_create(int size); |creates a new epoll(7) instance.|returns a file descriptor referring to the new epoll instance. This file descriptor is used for all the subsequent calls to the epoll interface. When no longer required, the file descriptor returned by epoll_create() should be closed by  using close. When all file descriptors referring to an epoll instance have been closed, the kernel destroys the instance and releases the associated resources for reuse. On error, -1 is returned, and errno is set to indicate the error.|
|int epoll_ctl(int epfd, int op, int fd, struct epoll_event * event);|is used to add, modify, or remove entries in the interest list of the epoll instance referred to by the file descriptor epfd. It requests that the operation op be performed for the target file descriptor, fd.|When successful, epoll_ctl() returns zero. When an error occurs, epoll_ctl() returns -1 and errno is set appropriately.|
|int epoll_wait(int epfd, struct epoll_event * events, int maxevents, int timeout);|waits for events on the epoll(7) instance referred to by the file          descriptor epfd.  The memory area pointed to by events will contain the events that will be available  for the caller. Up to maxevents are returned by epoll_wait().  The maxevents argument must be greater than zero. | When  successful,  epoll_wait() returns the number of file descriptors ready for the requested I/O, or zero if no file descriptor became ready during  the  requested  timeout  milliseconds. When an error occurs, epoll_wait() returns -1 and errno is set appropriately. |
|kqueue| | |
|kevent| | |
| int socket(int domain, int type, int protocol);|socket()  creates  an  endpoint  for communication and returns a file descriptor that refers to that endpoint.| On success, a file descriptor for the new socket is returned.  On error, -1 is returned, and errno is set  appropriately. |
|int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);|The  accept()  system  call is used with connection-based socket types (SOCK_STREAM, SOCK_SEQPACKET). It extracts the first connection request on the queue of pending connections for the listening socket, sockfd, creates a new connected socket, and returns a new file descriptor referring to that socket. The newly created socket is not in the listening state. The original socket sockfd is unaffected by this call. |On success, these system calls return a nonnegative integer that is a file descriptor for the accepted  socket. On error, -1 is returned, errno is set appropriately, and addrlen is left unchanged. |

 </details>
 
 
## study_resources

* [Overview Of World Wide Web by Arif Butt](https://www.youtube.com/watch?v=Ls2G6HjvkYc&list=PL7B2bn3G_wfD6_mhy-eLdn_mFgQ_mOyLl&index=11)
* [HTTP Server: Everything you need to know to Build a simple HTTP server from scratch](https://medium.com/from-the-scratch/http-server-what-do-you-need-to-know-to-build-a-simple-http-server-from-scratch-d1ef8945e4fa)
