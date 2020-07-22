//
//
//  Copyright (c)1992-2020,THS Stock CO.LTD.
//  All Rights Reserved.
//
//	Description: 日志工具类
//	Revisions:		2020-07-22  zhusaihui@myhexin.com
//
#pragma once
#include <string>
#include <time.h>
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>

const char * hqdir = "/var/log/hq";
const char * logfile = "var/log/hq/log";

void write(std::string str)
{
    std::fstream os;
    if (access(hqdir,0)){
        std::cout<<"dasda";
        mkdir(hqdir,S_IWGRP);
    }
    os.open(logfile,std::ios::app);
    os<<str<<std::endl;
}

void Log(std::string msg)
{
    time_t  timep;
    char timeStr[64];
    std::string result;
    strftime(timeStr,sizeof(timeStr),"%Y-%m-%d %H:%M:%S",localtime(&timep));
    result.append(timeStr);
    result.append("  ");
    result.append(msg);
    std::cout<<result<<std::endl;
    write(result);
}