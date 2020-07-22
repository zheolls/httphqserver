//
//
//  Copyright (c)1992-2020,THS Stock CO.LTD.
//  All Rights Reserved.
//
//	Description: 简易股票行情服务，提供同花顺（300033）的行情分时数据。
//	Revisions:		2020-07-21  zhusaihui@myhexin.com
//

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
#include "Log.cpp"
//同花顺股票行情
class StockHq{
private:
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
    
    /// \brief 设置event的时间参数
    void setTimeVal(int s,int us);

    /// \brief 处理http请求
    static void HttpServerHandler(evhttp_request *request,void *arg);

    /// \brief 设置监听端口
    void setPort(int port);

    void setBackLog(int backlog);

    /// \brief 套接字绑定
    int HttpServerBindSocket(int port,int backlog);

    /// \brief 开始HTTP服务
    int start();

    /// \brief 从URL参数列表中根据参数名获取参数值
    /// \param param 参数key
    /// \param params 参数列表
    std::string getParam(std::string param,evkeyvalq params);
};