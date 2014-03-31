#include "redis.h"


int main()
{
	//Redis *r = new Redis;

	//r->connect("127.0.0.1", 6379);
	//
	//r->set("foo", "hello zoujiaqing!");
	//r->hmset("man:1", "name zhangsan age 20 city bj");
	//r->hmset("man:2", "name lisi age 25 city sh");
	//r->hmset("man:3", "name wangwu age 20 city sz");
	//r->hmset("man:4", "name zhaoliu age 25 city bj");
	//r->hmset("man:5", "name maqi age 20 city sz");

	//r->sset("man", "name");

	////½¨Á¢Ë÷Òı
	//r->sset("man:age.20:id", "1 3 5");
	//r->sset("man:age.25:id", "2 4");

	//r->sset("man:name.zhangsan:id", "1");
	//r->sset("man:name.lisi:id", "2");
	//r->sset("man:name.wangwu:id", "3");
	//r->sset("man:name.zhaoliu:id", "4");
	//r->sset("man:name.maqi:id", "5");

	//r->sset("man:city.bj:id", "1 4");
	//r->sset("man:city.sh:id", "2");
	//r->sset("man:city.sz:id", "3 5");

	//r->hgetall("man:1");
	//r->sget("man");
	////r->select("select * from man");
	//printf("HGET: %s\n", r->hget("man:1", "name").c_str());

	//printf("GET: %s ", r->get("foo").c_str());

	WSADATA wsaData;  
	WSAStartup(MAKEWORD( 2, 2 ), &wsaData);  

	redisContext *test = redisConnect("127.0.0.1", 6379);
	//redisReply* ttt = (redisReply*)redisCommand(test, "HGET man:1 name");
	redisReply* ttt = (redisReply*)redisCommand(test, "smembers test");

	(**ttt->element).str;
	//ttt->element

	std::string str = ttt->str;

	
	return 0;
}