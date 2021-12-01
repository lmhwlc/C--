#pragma once
#include<string>
using namespace std;
class Satelite
{
private:
	//卫星的属性信息
	string name;			//卫星的名字
	bool JNX;				//标志卫星属于境内星还是境外星
	bool link;				//标志卫星是否连接通信
	bool send;				//卫星是否发送信息
	bool JL;				//卫星是否建链
	bool Normal;			//卫星是否正常运行
	bool visit;				//卫星是否被访问过
public:
	Satelite();
	~Satelite();
	void SetSateliteName(string);

	bool GetSateliteJNX();
	void SetSateliteJN_JW(bool);

	bool GetSateliteSend();
	void SetSateliteSend(bool);

	bool GetSateliteJL();
	void SetSateliteJL(bool);

	bool GetSatNormal();
	void SetSatNomral(bool);

	bool GetSatVisit();
	void SetSatVisit(bool);
};
