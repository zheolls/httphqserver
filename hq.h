#include <event.h>
#include <iostream>
#include <time.h>
#include <stdio.h>
#include <evhttp.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/types.h>

class StockHq{
private:
    int time;
    event hqev;
    event_base * httpbase = event_init();
    timeval tv;
    int port = 9090;
    int backlog = 128;
public:
    void GetHq();
    
    void SetTimeVal(int us);

    static void HttpServerHandler(evhttp_request *request,void *arg);

    void SetPort(int port);

    void SetBackLog(int backlog);

    int HttpServerBindSocket(int port,int backlog);

    int Start();
    
    std::string GetParam(std::string param,evkeyvalq params);
};