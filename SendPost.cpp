//
//
//  Copyright (c)1992-2020,THS Stock CO.LTD.
//  All Rights Reserved.
//
//	Description: 使用CURL库进行POST请求
//	Revisions:		2020-07-21  zhusaihui@myhexin.com
//


#include <curl/curl.h>
#include <string>
#include <iostream>
#include "Log.cpp"
/// \brief curl回调函数

size_t req_reply(void *ptr, size_t size, size_t nmemb, void *stream)
{
    // std::string *str = (std::string*)stream;
    // (*str).append((char*)ptr, size*nmemb);
    // Log("Length:"+std::to_string((*str).length()));
	return size * nmemb;
}

/// @brief Post指定参数到对应URL

/// @param strPostUrl 需要post的地址 e.g. 'http://10.10.80.43:8080/hexin'
/// @param strPostParams 请求的url参数 e.g. 'key1=value1&key2=value2&...' 
/// @param strPostResults 请求应答结果

void SendPost(const std::string& strPostUrl,const std::string& strPostParams,std::string& strPostResults){
    
    //curl初始化
    curl_global_init(CURL_GLOBAL_ALL);
    int nTimeOut = 3;
    int nConnectTimeOut = 3;
    CURL * curl = curl_easy_init();
    CURLcode res;

    if (curl)
    {
        // 设置各项请求参数
        curl_easy_setopt(curl,CURLOPT_POST,1);
        curl_easy_setopt(curl,CURLOPT_URL,strPostUrl.c_str()); //设置URL
        curl_easy_setopt(curl,CURLOPT_POSTFIELDS,strPostParams.c_str()); //设置参数
        curl_easy_setopt(curl,CURLOPT_SSL_VERIFYPEER,false);
        curl_easy_setopt(curl,CURLOPT_SSL_VERIFYHOST,false);
        curl_easy_setopt(curl,CURLOPT_VERBOSE,1);
        curl_easy_setopt(curl,CURLOPT_READFUNCTION,NULL);
        curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,req_reply);
        curl_easy_setopt(curl,CURLOPT_WRITEDATA,(void*)&strPostResults);
        curl_easy_setopt(curl,CURLOPT_NOSIGNAL,1);
        curl_easy_setopt(curl,CURLOPT_HEADER,1);
        curl_easy_setopt(curl,CURLOPT_CONNECTTIMEOUT,nConnectTimeOut);
        curl_easy_setopt(curl,CURLOPT_TIMEOUT,nTimeOut);
        res = curl_easy_perform(curl); //发送请求

    }
    curl_easy_cleanup(curl);

    if (res!=CURLE_OK)
    {
        Log("Send Request Failed " + std::string(curl_easy_strerror(res)));

    }
    curl_global_cleanup();
    
}
