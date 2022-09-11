# webserv

* [introduction](#introduction)
* [socket](#socket)
* [Configuration_file](#Configuration_file)
    * [server_blocks](#server_blocks)
      * [listen](#listen)
      * [server_name](#server_name)
      * [location](#location)
      * [client_body_size](#client_body_size)
      * [error_page](#error_page)
    * [how_nginx_processes_a_request](#how_nginx_processes_a_request)
* [parser](#parser)
* [HTTP](#HTTP)
  * [client](#client)
  * [user_agent](#user_agent)
  * [server](#server)
  * [proxy](#proxy)
  * [gateway](#gateway)
  * [cache](#cache)
  * [Request](#Request)
    * [Request-Line](#Request-Line)
    * [Request-Line](#Request-Line)
    * [Response_Header_Fields](#Response_Header_Fields)
  * [Response](#Response)
    * [Status-Line](#Status-Line)
    * [Request-Line](#Request-Line)
    * [Request_Header_Fields](#Request_Header_Fields)
* [ifstream](#ifstream)
* [specific_functions_overview](#specific_functions_overview)
* [study resources](#study_resources)



![webserv-ex (1)](https://user-images.githubusercontent.com/63563271/189550914-a28ee028-5503-4585-a544-38a2542bfba2.gif)


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

> note that any software program that does the same as a web browser (ie: retrieve documents from servers) is called a **client** in network terminology and a **user agent** in web terminology. Also note that the **server is** properly the **server program**, and **not the computer** on which the server is an application program. (Sometimes called the server machine.)


![webserv-error (1)](https://user-images.githubusercontent.com/63563271/189550912-989d56d2-9d8f-477a-a070-c6366fd352f1.gif)
![webserv-ex2](https://user-images.githubusercontent.com/63563271/189551453-cb12c906-646d-4fb0-a169-271edb911e36.gif)

![image](https://user-images.githubusercontent.com/63563271/189552075-7b119358-e3a2-4582-8189-850b7d94fb7a.png)

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

## Configuration_file

(based on NGNIX)

configurations are setup is by:

* directives - configuration options
* Blocks (also known as contexts) - Groups in which Directives are organized

* any character after # in a line becomes a comment

### server_blocks

Server configuration files contain a server block for a website.

#### listen

**The server configuration block usually includes a listen directive to specify the IP address and port on which the server listens for requests.**

[NGINX listen docs](https://nginx.org/en/docs/http/ngx_http_core_module.html#listen)

On Nnginx, both address and port, or only address or only port can be specified. An address may also be a hostname

```
listen 127.0.0.1:8000;
listen 127.0.0.1;
listen 8000;
listen *:8000;
listen localhost:8000;
```

On Nignx, `backlog=number` sets the backlog parameter in the listen() call that limits the maximum length for the queue of pending connections.
By default, backlog is set to 511 on Linux

```
listen localhost:8000 backlog=1024
```

On Nginx, you [can have multiple listen directives per server](https://stackoverflow.com/questions/38051198/nginx-how-to-setup-multiple-port-in-one-server-or-domain-name):

```
server {
 listen 5005 ssl;
 listen 6006 ssl;
 server_name <https - mydomainname>;
 ssl_certificate <location cert>;
 ssl_certificate_key <location key>;
  location /tags.txt {
    add_header 'Access-Control-Allow-Origin' '*';
  }
```

#### server_name

Allows multiple domains to be served from a single IP address. Ideally, it should be created per domain or site. Based on the request header it receives, the server decides which domain to serve.

> In catch-all server examples the strange name “_” can be seen There is nothing special about this name, it is just one of a myriad of invalid domain names which never intersect with any real name. Other invalid names like “--” and “!@#” may equally be used.

[This](https://serverfault.com/questions/914906/what-is-the-difference-between-server-name-and-server-name-in-nginx) and [this](https://stackoverflow.com/questions/9454764/nginx-server-name-wildcard-or-catch-all
) are interesting threads about `_` and `""`

[NGINX server_name docs](http://nginx.org/en/docs/http/server_names.html)

#### location

Location directives cover requests for specific files and folders. It also allows NGINX to respond to requests for resources within the server.

The locations are literal string matches:

```
server_name example.com

location / { }
location /images/ { }
location /blog/ { }
location /planet/ { }
location /planet/blog/ { }
```
a request to http://example.com/planet/blog/ or http://example.com/planet/blog/about/ is fulfilled by location /planet/blog/ , even though location /planet/ also matches this request.

##### Set location to a different directory

```
location /subdir {
    root /srv/http/someplace;
    index index.html;
   ...
}
```

##### Methods allowed

`allow_methods "^(GET|POST|PUT|DELETE|PATCH|LINK|COPY)$";`
[module to allow http methods on nginx](https://github.com/pschultz/ngx_http_allow_methods_module):
```
    server {

        location /api/ {
            allow_methods ".*";
        }

    }
```

##### Redirection

HTTP redirection is way to point one domain or address to another. There are a few different kinds of redirects, each of which mean something different to the client browser. The two most common types are temporary redirects and permanent redirects.

Temporary redirects (response status code 302 Found) are useful if a URL temporarily needs to be served from a different location. For example, if you are performing site maintenance, you may wish to use a temporary redirect from your domain to an explanation page to inform your visitors that you will be back shortly.

Permanent redirects (response status code 301 Moved Permanently), on the other hand, inform the browser that it should forget the old address completely and not attempt to access it anymore. These are useful when your content has been permanently moved to a new location, such as when you change domain names.

Temporary redirect:
```
server {
    . . .
    server_name www.domain1.com;
    rewrite ^/$ http://www.domain2.com redirect;
    . . .
}
```

Permanent redirect:
```
rewrite ^/$ http://www.domain2.com permanent;
```

From Digital Ocean [How To Create Temporary and Permanent Redirects with Nginx](https://www.digitalocean.com/community/tutorials/how-to-create-temporary-and-permanent-redirects-with-nginx)


##### autoindex

Without `autoindex` option you should be getting Error 403 for** requests that end with / on directories that do not have an index.html file**. With this option you should be getting a simple listing:

```html
<html>
<head><title>Index of /</title></head>
<body bgcolor="white">
<h1>Index of /test/</h1><hr><pre><a href="../">../</a>
<a href="test.txt">test.txt</a>
</pre><hr></body>
</html>
```

##### default files

`index` defines files that will be used as an index to requests ending with the slash character (‘/’).

````
location / {
  index index.html;
}
````

[Nginx index](http://nginx.org/en/docs/http/ngx_http_index_module.html)

#### client_body_size

On Nginx `client_max_body_size` sets the maximum allowed size of the **client request body**. If the size in a request exceeds the configured value, the **413** (Request Entity Too Large) error is returned to the client. Please be aware that browsers cannot correctly display this error. Setting size to 0 disables checking of client request body size.

Default:

```
client_max_body_size 1m
```

[NGINX client_max_body_size docs](https://nginx.org/en/docs/http/ngx_http_core_module.html#client_max_body_size)

#### error_page

Defines the URI that will be shown for the specified errors.

```
error_page 404             /404.html;
error_page 500 502 503 504 /50x.html;
```

[NGINX error_page docs](https://nginx.org/en/docs/http/ngx_http_core_module.html#error_page)


### how_nginx_processes_a_request

#### if listen diretive are the same:

```
server {
    listen      80;
    server_name example.org www.example.org;
    ...
}

server {
    listen      80;
    server_name example.net www.example.net;
    ...
}

server {
    listen      80;
    server_name example.com www.example.com;
    ...
}
```

* decides which server should process the request based on the **request’s header** field `Host`
* If its value does not match any server name then nginx will route the request to the default server for this port. The default server is the first one
* If requests without the “Host” header field should not be allowed, a server that just drops the requests can be defined:
```
server {
    listen      80;
    server_name "";
    return      444;
}
```

#### if listen diretive are different:

```
server {
    listen      192.168.1.1:80;
    server_name example.org www.example.org;
    ...
}

server {
    listen      192.168.1.1:80;
    server_name example.net www.example.net;
    ...
}

server {
    listen      192.168.1.2:80;
    server_name example.com www.example.com;
    ...
}
```

* first tests the IP address and port of the request against the listen directives of the server blocks
* then tests the “Host” header field of the request against the server_name entries of the server blocks that matched the IP address and port
*If the server name is not found, the request will be processed by the default server (first of the possibles ones)

[more infos](http://nginx.org/en/docs/http/request_processing.html)

## parser

![image](https://user-images.githubusercontent.com/63563271/189551799-df567ed8-63ae-495d-a49e-1ce86ca3dc3c.png)


**SERVER**
| directive | quantity | type | mandatory |
|----------|-----------|-------|---------|
|listen|1 (or + ?)|pair/struct/class|:heavy_check_mark: 80 by default?|
|server_name|1|string/string list|:heavy_check_mark:|
|root|string|1|:heavy_check_mark:|
|error pages|1 + default|string|:x:|
|CGI|1 or +|Cgi object|:x:|
|client body size|1|string/int|:x:|
|location|1 or +|string|:x:|

**LOCATION**
| directive | quantity | type | mandatory |
|----------|-----------|-------|---------|
|accepted methods|1|string/string list|:x: GET by default?|
|redirection|1|string|:x:|
|root|1|string|:x: if not, location path is used|
|autoindex|1|bool|:x: false by default|
|index|1|string/string list|:x:|
|client body size|1|string/int|:x:|
|CGI|1 or +|Cgi object|:x:|
|error pages|1 + default|string|:x:|
|prefix|1|string|:heavy_check_mark:|

Other important infos:

* Make the route able to accept uploaded files and configure where they should be saved
* The first server for a host:port will be the default for this host:port

## HTTP

The HTTP protocol is a **request/response protocol**.

A **client** sends a **request to the server** in the form of a request method, URI, and protocol version, followed by a MIME-like message containing request modifiers, client information, and possible body content over a connection with a server.

The **server responds** with a status line, including the message's protocol version and a success or error code, followed by a MIME-like message containing server information, entity metainformation, and possible entity-body content.

Most HTTP communication is **initiated by a user agent** and consists of a **request to be applied to a resource on some origin server**. In the simplest case, this may be accomplished via a single connection between the user agent and the origin server.

A more complicated situation occurs when one or more intermediaries are present in the request/response chain.

In **HTTP/1.1**, a connection may be used for **one or more request/response exchanges**, although connections may be closed for a variety of reasons.

The "http" scheme is used to locate network resources via the HTTP protocol. This scheme-specific syntax and semantics for http URLs is:

   `http_URL = "http:" "//" host [ ":" port ] [ abs_path [ "?" query ]]`

**If the port is empty or not given, port 80 is assumed.**


The HTTP protocol **does not place any a priori limit on the length of a URI**. Servers MUST be able to handle the URI of any resource they serve, and SHOULD be able to handle URIs of unbounded length if they provide GET-based forms that could generate such URIs. **A server SHOULD return 414 (Request-URI Too Long) status if a URI is longer than the server can handle**.


### client

A **program** that **establishes connections** for the purpose of **sending requests**.

### user_agent

The **client which initiates a request**. These are often browsers, editors, spiders (web-traversing robots), or other end user tools.

### server

An **application program** that **accepts connections** in order to **service requests by sending back responses**.

**Any given program** may be capable of being **both** a client and a server; our use of these terms refers only to the **role being performed** by the program **for a particular connection**, rather than to the program's capabilities in general. Likewise, any server may act as an origin server, proxy, gateway, or tunnel, switching behavior based on the nature of each request.

### proxy

An **intermediary program** which **acts as both a server and a client** for the purpose of **making requests** on **behalf** of **other clients**. Requests are serviced internally or by passing them on, with possible translation, to other servers.

A proxy MUST implement both the client and server requirements of this specification. 

A **"transparent proxy"** is a proxy that **does not modify the request or response** beyond what is required for proxy authentication and identification. 

A **"non-transparent proxy"** is a proxy that **modifies the request or response** in order **to provide some added service to the user agent**, such as group annotation services, media type transformation, protocol reduction, or anonymity filtering.

Except where either transparent or non-transparent behavior is explicitly stated, the HTTP proxy requirements apply to both types of proxies.

### gateway

A **server** which acts as an **intermediary** for some **other server**. Unlike a proxy, a gateway **receives requests as if it were the origin server for the requested resource**; the requesting client may not be aware that it is communicating with a gateway.

### cache

A **program's local store** of response messages and the subsystem
that controls its message storage, retrieval, and deletion.

A cache stores cacheable responses in order to **reduce the response time and network bandwidth consumption on future** equivalent requests.

Any client or server may include a cache, though a cache cannot be used by a server that is acting as a tunnel.

### Request

A request message from a client to a server includes, within the first line of that message, the method to be applied to the resource, the identifier of the resource, and the protocol version in use.

#### Request-Line

The Request-Line begins with a method token, followed by the Request-URI and the protocol version, and ending with CRLF. The elements are separated by SP characters. No CR or LF is allowed except in the final CRLF sequence.

`Request-Line = Method SP Request-URI SP HTTP-Version CRLF`

The `Method`  token indicates the method to be performed on the resource identified by the Request-URI. The method is case-sensitive

|Method|
|----------|
|"OPTIONS" |
| "GET"     |
| "HEAD"    |
| "POST"    |
| "PUT"     |
| "DELETE"  |
| "TRACE"   |
| "CONNECT" |

The list of methods allowed by a resource can be specified in an **Allow header field**.

The return code of the **response always notifies** the client whether a **method is currently allowed on a resource**, since the set of allowed methods can change dynamically. 

An origin server SHOULD return the status code **405** (Method Not Allowed) if the method is **known by the origin server but not allowed for the requested resource**, and **501** (Not Implemented) if the method is **unrecognized or not implemented by the origin server**. The methods **GET** and **HEAD** **MUST be supported** by all general-purpose servers. **All other** methods are **OPTIONAL**.

The `Request-URI` is a Uniform Resource Identifier (section 3.2) and identifies the resource upon which to apply the request.

#### Request_Header_Fields

The request-header fields allow the client to pass additional information about the request, and about the client itself, to the server.

|Request Header|
|--------------|
| Accept             |
| Accept-Charset     |
| Accept-Encoding    |
| Accept-Language    |
| Authorization      |
| Expect             |
| From               |
| Host               |
| If-Match           |
| If-Modified-Since  |
| If-None-Match      |
| If-Range           |
| If-Unmodified-Since|
| Max-Forwards       |
| Proxy-Authorization|
| Range              |
| Referer            |
| TE                 |
| User-Agent         |

### Response
After receiving and interpreting a request message, a server responds with an HTTP response message.

#### Status-Line

The first line of a Response message is the Status-Line, consisting of the protocol version followed by a numeric status code and its associated textual phrase, with each element separated by SP characters. No CR or LF is allowed except in the final CRLF sequence.

`Status-Line = HTTP-Version SP Status-Code SP Reason-Phrase CRLF`

The `Status-Code` element is a 3-digit integer result code of the attempt to understand and satisfy the request.
The `Reason-Phrase` is intended to give a short textual description of the `Status-Code`. The `Status-Code` is intended for use by automata and the `Reason-Phrase` is intended for the human user. The client is not required to examine or display the `Reason-Phrase`.

The first digit of the `Status-Code` defines the class of response. The last two digits do not have any categorization role. There are 5 values for the first digit:

- `1xx`: Informational - Request received, continuing process
- `2xx`: Success - The action was successfully received, understood, and accepted
- `3xx`: Redirection - Further action must be taken in order to complete the request
- `4xx`: Client Error - The request contains bad syntax or cannot be fulfilled
- `5xx`: Server Error - The server failed to fulfill an apparently valid request

### Response_Header_Fields

The response-header fields allow the server to pass additional information about the response. These header fields give information about the server and about further access to the resource identified by the Request-URI.

|Response Header|
|---------------|
| Accept-Ranges      |
| Age                |
| ETag               |
| Location           |
| Proxy-Authenticate |
| Retry-After        |
| Server             |
| Vary               |
| WWW-Authenticate   |

### Connection_Field

The Connection general-header field allows the sender to specify options that are desired for that particular connection and MUST NOT be communicated by proxies over further connections.

HTTP/1.1 defines the "close" connection option for the sender to signal that the connection will be closed after completion of the response. In either the request or the response header fields indicates that the connection SHOULD NOT be considered [persistent](https://www.rfc-editor.org/rfc/rfc2616#section-8.1) after the current request/response is complete.

HTTP/1.1 applications that do not support persistent connections MUST include the "close" connection option in every message.

### ifstream

Flags describing the requested i/o mode for the file:
(These flags can be combined with the bitwise OR operator `|`)

|member constant|stands for|access|
|---------------|----------|------|
|in |input|File open for reading: the internal stream buffer supports input operations.|
|out|output|File open for writing: the internal stream buffer supports output operations.|
|binary|binary|Operations are performed in binary mode rather than text.|
|ate|at end|The output position starts at the end of the file.|
|app|append|All output operations happen at the end of the file, appending to its existing contents.|
|trunc|truncate|Any contents that existed in the file before it is open are discarded.|

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
* [How the web works: HTTP and CGI explained](https://www.garshol.priv.no/download/text/http-tut.html)
* [RFC 2616](https://datatracker.ietf.org/doc/html/rfc2616)
* [How nginx processes a request](http://nginx.org/en/docs/http/request_processing.html)
* [Curl POST examples](https://gist.github.com/subfuzion/08c5d85437d5d4f00e58)
* [Multipart formposts](https://everything.curl.dev/http/multipart#:~:text=A%20multipart%20formpost%20is%20what,%22%2C%20separated%20with%20MIME%20boundaries.)
* ['x-www-form-urlencoded' or 'form-data'?](https://dev.to/getd/x-www-form-urlencoded-or-form-data-explained-in-2-mins-5hk6)
* [stackoverflow thread what-is-the-right-way-to-post-multipart-form-data-using-curl](https://stackoverflow.com/questions/19116016/what-is-the-right-way-to-post-multipart-form-data-using-curl)
