# 简单行情服务

## 依赖库

libevent、curl
安装
```bash
yum install libcurl4-openssl-dev libevent-dev
```

## 安装

```bash
g++ -o thshqserver main.cpp -levent -lcurl
sudo mv thshqserver /usr/bin
```

## 运行

```bash
thshqserver
```

## 调用方法

### CURL示例
```bash
curl 'http://[YOURIP]:9090/' -d 'datetime=8192(0-0)&datatype=10,13'
```

### 参数说明

|参数|类型|描述|示例|
| ---- | ---- | ----|----|
|datetime|string|周期 时间段 偏移|8192(0-0)|
|datatype|string|请求指标，详见Wiki|10,13|

### 返回参数说明
```xml

<Result>
    <DataResult>
        <CodeIndex>
            记录列表
            <Record>
                <Item id="1">
                    <Value>
                        时间，秒数格式，详见wiki
                    </Value>
                </Item>
                请求的其他指标
                ...
            </Record>
                ...
        </CodeIndex>
    </DataResult>

</Result>
```