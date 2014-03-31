#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <winsock2.h>  
#include <iostream>  

#include "hiredis.h"  

#pragma warning(disable: 4996)  
//#pragma comment(lib, "ws2_32.lib")  

class Redis  
{  
public:  

	Redis()  
	{  
		WSADATA wsaData;  
		WSAStartup(MAKEWORD( 2, 2 ), &wsaData);  
	}  

	~Redis()  
	{  
		this->_connect = NULL;  
		this->_reply = NULL;  
	}  

	bool connect(std::string host, int port)  
	{  
		this->_connect = redisConnect(host.c_str(), port);  
		if (this->_connect->err) {  
			return false;  
		}  
		return true;  
	}  

	std::string getError()  
	{  
		return this->_connect->errstr;  
	}  

	std::string get(std::string key)  
	{  
		this->_reply = (redisReply*)redisCommand(this->_connect, "GET %s", key.c_str());  
		std::string str = this->_reply->str;

		freeReplyObject(this->_reply);  

		return str;  
	}  

	void set(std::string key, std::string value)  
	{  
		redisCommand(this->_connect, "SET %s %s", key.c_str(), value.c_str());  
	}

	std::string hget(std::string key, std::string field)
	{
		this->_reply = (redisReply*)redisCommand(this->_connect, "HGET %s %s", key.c_str(), field.c_str());
		std::string str = this->_reply->str;

		freeReplyObject(this->_reply);

		return str;
	}
	
	void hset(std::string key, std::string field, std::string value)
	{
		redisCommand(this->_connect, "HSET %s %s %s",  key.c_str(), field.c_str(), value.c_str());
	}

	void hmset(std::string key, std::string value)
	{
		char buf[256];
		sprintf(buf, "HMSET %s %s", key.c_str(), value.c_str());
		redisCommand(this->_connect, buf);
	}

	std::string hgetall(std::string key)
	{
		char buf[256];
		sprintf(buf, "hgetall %s ", key.c_str());
		
		this->_reply = (redisReply*)redisCommand(this->_connect, buf);

		

		std::string str = this->_reply->str;

		freeReplyObject(this->_reply);

		return str;
	}

	std::string sget(std::string key)
	{
	//	freeReplyObject(this->_reply);
		
		char buf[256];
		sprintf(buf, "SMEMBERS %s", key.c_str());
		this->_reply = (redisReply*)redisCommand(this->_connect, "SMEMBERS %s", key.c_str());
		std::string str; 
		this->_reply->str;

		freeReplyObject(this->_reply);

		return str;
	}
	
	void sset(std::string key, std::string value)
	{
		redisCommand(this->_connect, "SADD %s %s", key.c_str(), value.c_str());
	}

	void select(std::string sql)
	{
		const char *p = sql.c_str();
		const char *pp;
		std::string str;
		if(strstr(p, "*"))
		{
			char *c = " ";
			pp = strrchr(p, int(*c));
			//string str = sget()

			str = pp + 1;
		}

		std::string strKey = str.append(":fields");
		std::string strFields = sget(strKey);
	}

	

private:  
	redisContext* _connect;  
	redisReply* _reply;  
}; 