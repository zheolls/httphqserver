#include <curl/curl.h>
#include <string>
#include <iostream>
std::string * req_reply(void * ptr ,size_t size ,size_t nmemb,void *stream){
    std::string * str = (std::string *)stream;
    std::cout<<*str<<std::endl;
    (*str).append((char*)ptr,size*nmemb);
    return str;
}


void SendPost(const std::string& strPostUrl,const std::string& strPostParams,std::string& strPostResults){
    curl_global_init(CURL_GLOBAL_ALL);
    int nTimeOut = 3;
    int nConnectTimeOut = 3;
    CURL * curl = curl_easy_init();
    CURLcode res;
    if (curl)
    {
        curl_easy_setopt(curl,CURLOPT_POST,1);
        curl_easy_setopt(curl,CURLOPT_URL,strPostUrl.c_str());
        curl_easy_setopt(curl,CURLOPT_POSTFIELDS,strPostParams.c_str());
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
        res = curl_easy_perform(curl);

    }
    curl_easy_cleanup(curl);

    if (res!=CURLE_OK)
    {
        std::cout<<"Send Request Failed" + std::string(curl_easy_strerror(res))<<std::endl;

    }
    curl_global_cleanup();
    
}