#include "HqServer.h"
#include "SendPost.cpp"
#define HQQUOTAURL "http://10.10.80.140:8080/hexin"
void StockHq::setPort(int port){
    this->port = port;
}

void StockHq::setBackLog(int backlog){
    this->backlog = backlog;
}
void StockHq::getHq(){

}    
void StockHq::setTimeVal(int s,int us){
    this->tv.tv_sec = s;
    this->tv.tv_usec = us;
};

void StockHq::HttpServerHandler(evhttp_request *request,void *arg){
	evbuffer *buf = evbuffer_new();
    evkeyvalq params;
	if (buf == NULL) 
	{
		printf("evbuffer_new error !\n");
		return;
	}
    const char * url = evhttp_request_uri(request);
    std::cout<<url<<std::endl;
    evhttp_parse_query(url,&params);

    evhttp_cmd_type cmdtype = evhttp_request_get_command(request);
    if (cmdtype == EVHTTP_REQ_GET)
    {
        std::cout<<"GET正确"<<std::endl;
    }
    else
    {
        /* code */
    }
    evkeyval * ev = params.tqh_first;
    while (ev)
    {
        std::cout<<"Key:"<<ev->key<<" Value:"<<ev->value<<std::endl;
        ev = ev->next.tqe_next;
    }
    
    //header
    //X-Arsenal-Auth arsenal-tools

    //params
    //begintime 20200114 
    //endtime 20200114
    //datatype 7,8
    //codelist 33(300033)
    //fuquan q
    const char * datetime = evhttp_find_header(&params,"datetime");
    const char * datatype = evhttp_find_header(&params,"datatype");

    std::string postresults;

    if (datetime!=0 && datatype!=0)
    {
        std::string postparmas = "method=quote&code=300033";
        postparmas.append("&datetime=");
		postparmas.append(datetime);
        postparmas.append("&datatype=");
		postparmas.append(datatype);
        SendPost(HQQUOTAURL,postparmas,postresults);

    }
    
	evbuffer_add_printf(buf,postresults.c_str());
	evhttp_send_reply(request, 200, "OK", buf);  
}

std::string StockHq::getParam(std::string param,evkeyvalq params){
    std::string result;
    evkeyval * evk = params.tqh_first;
    while (evk){
        if (evk->key==param)
        {
            return evk->value;
        }
        evk = evk->next.tqe_next;
    }
    return NULL;
    
}

int StockHq::HttpServerBindSocket(int port,int backlog){
    int ret;
	int fd;
	fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd < 0) 
	{
		printf("socket error !\n");
		return -1;
	}
 
	int opt = 1;
	ret = setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(int));
 
	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(port);
 
	ret = bind(fd, (struct sockaddr*)&addr, sizeof(addr));
	if (ret < 0) 
	{	
		printf("bind error !\n");
		return -1;
	}
	ret = listen(fd, backlog);
	if (ret < 0) 
	{
		printf("listen error !\n");
		return -1;
	}
 
	int flags;
	if ((flags = fcntl(fd, F_GETFL, 0)) < 0
		|| fcntl(fd, F_SETFL, flags | O_NONBLOCK) < 0)
	{
		printf("fcntl error !\n");
		return -1;
	}
	return fd;
}

int StockHq::start(){
    int ret;
	int fd = HttpServerBindSocket(this->port, this->backlog);
	if (fd < 0) 
	{	
		return -1;
		printf("httpserver_bindsocket error !\n");
	}
	struct event_base *base = event_init();
	if (base == NULL) 
	{
		printf("event_init error !\n");
		return -1;		
	}
	struct evhttp *httpd = evhttp_new(base);
	if (httpd == NULL) 
	{
		printf("enhttp_new error !\n");
		return -1;
	}
	ret = evhttp_accept_socket(httpd, fd);
	if (ret != 0) 
	{
		printf("evhttp_accept_socket error \n");
		return -1;
	}
	evhttp_set_gencb(httpd, HttpServerHandler, NULL);
	event_base_dispatch(base);
	return 0;
}
