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

//同花顺股票行情
class StockHq{
private:
    int time;
    event hqev;
    event_base * httpbase;
    timeval tv;
    int port;
    int backlog;
public:
    
    StockHq(){
        httpbase = event_init();
        port = 9090;
        backlog = 128;
    }
    
    void getHq();
    //设置event的时间参数
    void setTimeVal(int s,int us);

    static void HttpServerHandler(evhttp_request *request,void *arg);

    void setPort(int port);

    void setBackLog(int backlog);

    int HttpServerBindSocket(int port,int backlog);

    int start();
    
    std::string getParam(std::string param,evkeyvalq params);
};